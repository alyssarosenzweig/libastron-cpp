#include <bamboo/wire/Datagram.h>
#include <AIRepository.h>
#include <msgtypes.h>
#include <DistributedObject.h>

class LoginManager : public DistributedObject {
public:
	LoginManager(uint64_t do_id) : DistributedObject(do_id) {};
	void fieldUpdate(string fieldName, vector<Value> arguments) {
		cout << "LoginManager update on field " << fieldName << endl;
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

	repo.subscribe_channel(&loginWatcher);

	repo.loop();
}