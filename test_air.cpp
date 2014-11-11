#include <bamboo/wire/Datagram.h>
#include <bamboo/module/Numeric.h>
#include <AIRepository.h>
#include <msgtypes.h>
#include <DistributedObject.h>

class DistributedAvatar : public DistributedObject {
public:
	DistributedAvatar() : DistributedObject() {
		m_x = 0;
		m_y = 0;
		m_z = 0;
		m_h = 0;
	};

	string classname() { return "DistributedAvatar"; };

	bool fieldUpdate(string fieldName, vector<Value*> arguments) {
		cout << "Unhandled fieldUpdate " << fieldName << " for avatar " << m_do_id << endl;
		return false;
	}

	vector<Value*> get(string fieldName) {
		if(fieldName == "setXYZH") {
			Value* x = new Value(new Numeric(kTypeFloat32));
			Value* y = new Value(new Numeric(kTypeFloat32));
			Value* z = new Value(new Numeric(kTypeFloat32));
			Value* h = new Value(new Numeric(kTypeFloat32));

			x->float_ = m_x;
			y->float_ = m_y;
			z->float_ = m_z;
			h->float_ = m_h;

			return vector<Value*>{ x, y, z, h };
		} else {
			cout << "DistributedAvatar unknown field " << fieldName << " requested" << endl;
			return vector<Value*>{};
		}
	}
private:
	float m_x, m_y, m_z, m_h;
};

class DistributedMaproot : public DistributedObject {
public:
	DistributedMaproot() : DistributedObject() {};
	string classname() { return "DistributedMaproot"; };

	bool fieldUpdate(string fieldName, vector<Value*> arguments) {
		if(fieldName == "createAvatar") {
			return createAvatar(arguments[0]->uint_);
		}

		return false;
	}

	bool createAvatar(uint64_t channel) {
		cout << "Create avatar at channel " << channel << endl;

		DistributedAvatar avatar;
		avatar.setCR(m_cr);
		avatar.generateWithRequired(10000, 0);

		((AIRepository*) m_cr)->client_add_interest(channel, 0, m_do_id, 0);
		((AIRepository*) m_cr)->set_owner(avatar.getDoId(), channel);

		return true;
	}
};

class LoginManager : public DistributedObject {
public:
	LoginManager(uint64_t do_id) : DistributedObject(do_id) {};
	string classname() { return "LoginManager"; };

	bool fieldUpdate(string fieldName, vector<Value*> arguments) {
		cout << "LoginManager " << fieldName << " updated" << endl;

		if(fieldName == "login") {
			return login(arguments[0]->string_, arguments[1]->string_);
		}

		return false;
	};

	bool login(string username, string password) {
		uint64_t sender = ((AIRepository*) m_cr)->get_message_sender();

		cout << "Login attempt at channel " << sender 
			 << " from " << username 
			 << " with pass " << password
			 << endl;
		
		if(username == "guest" && password == "guest") {
			Value* channel = new Value(new Numeric(kTypeUint64));
			channel->uint_ = sender;

			((AIRepository*) m_cr)->set_client_state(sender, 2);
			m_maproot->sendUpdate("createAvatar", vector<Value*> {channel});
		}
		return true;
	};

	void setMaproot(DistributedMaproot* maproot) {
		m_maproot = maproot;
	};

private:
	DistributedMaproot* m_maproot;
};


int main() {
	boost::asio::io_service io_service;
	AIRepository repo(&io_service, "localhost", 7199, "simple_example.dc", 1337, 402000);

	Datagram dg;
	repo.control_header(&dg, CONTROL_SET_CON_NAME);
	dg.add_string("libastron-c++");
	repo.send(dg);

	LoginManager loginWatcher(1234);
	loginWatcher.setCR(&repo);
	repo.registerDOG(&loginWatcher);
	repo.subscribe_channel(&loginWatcher);

	DistributedMaproot maproot;
	maproot.setCR(&repo);
	maproot.generateWithRequiredAndId(10000, 0, 1);
	repo.set_ai(&maproot);

	loginWatcher.setMaproot(&maproot);

	repo.loop();
}