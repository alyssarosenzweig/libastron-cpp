#include <bamboo/wire/Datagram.h>
#include <AIRepository.h>
#include <msgtypes.h>
#include <DistributedObject.h>

class LoginManager : public DistributedObject {
public:
	LoginManager(uint64_t do_id) : DistributedObject(do_id) {};

	bool fieldUpdate(string fieldName, vector<Value*> arguments) {
		cout << "LoginManager " << fieldName << " updated" << endl;

		if(fieldName == "login") {
			return login(arguments[0]->string_, arguments[1]->string_);
		}

		return false;
	}

	bool login(string username, string password) {
		uint64_t sender = ((AIRepository*) m_cr)->get_message_sender();

		cout << "Login attempt at channel " << sender 
			 << " from " << username 
			 << " with pass " << password
			 << endl;
		
		if(username == "guest" && password == "guest") {
			((AIRepository*) m_cr)->set_client_state(sender, 2);
		}
		return true;
	}
};

class DistributedMaproot : public DistributedObject {
public:
	DistributedMaproot(uint64_t do_id) : DistributedObject(do_id) {};

	bool fieldUpdate(string fieldName, vector<Value> arguments) {
		if(fieldName == "createAvatar") {
			return createAvatar(arguments[0]->uint_);
		}
	}

	bool createAvatar(uint64_t channel) {
		cout << "Create avatar at channel " << channel;
	}
};

int main() {
	boost::asio::io_service io_service;
	AIRepository repo(&io_service, "localhost", 7199, "simple_example.dc", 1337);

	Datagram dg;
	repo.control_header(&dg, CONTROL_SET_CON_NAME);
	dg.add_string("libastron-c++");
	repo.send(dg);

	LoginManager loginWatcher(1234);
	loginWatcher.setCR(&repo);

	repo.subscribe_channel(&loginWatcher);

	repo.loop();
}