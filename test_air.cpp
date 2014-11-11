#include <bamboo/wire/Datagram.h>
#include <AIRepository.h>
#include <msgtypes.h>
#include <DistributedObject.h>

class LoginManager : public DistributedObject {
public:
	LoginManager(uint64_t do_id) : DistributedObject(do_id) {};

	bool fieldUpdate(string fieldName, vector<Value> arguments) {
		cout << "LoginManager " << fieldName << " updated" << endl;

		if(fieldName == "login") {
			return login(arguments[0].string_, arguments[0].string_);
		}

		return false;
	}

	bool login(string username, string password) {
		cout << "Login attempt from " << username << " with pass " << password << endl;
		return true;
	}
};

int main() {
	boost::asio::io_service io_service;
	AIRepository repo(&io_service, "localhost", 7199, "simple_example.dc");

	Datagram dg;
	repo.control_header(&dg, CONTROL_SET_CON_NAME);
	dg.add_string("libastron-c++");
	repo.send(dg);

	LoginManager loginWatcher(1234);
	loginWatcher.setCR(&repo);

	repo.subscribe_channel(&loginWatcher);

	repo.loop();
}