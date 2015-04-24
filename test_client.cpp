#include <ClientRepository.h>
#include <DistributedObject.h>
#include <global.h>
#include <bamboo/module/Numeric.h>
#include <bamboo/module/NumericRange.h>
#include <bamboo/module/Array.h>
#include <DValue.hpp>

class LoginManager : public DistributedObject {
public:
	LoginManager(uint64_t do_id) : DistributedObject(do_id) {};
	string classname() { return "LoginManager"; };

	void sendLogin(string username, string password) {
		vector<DValue> args{ $(username), $(password) };
		sendUpdate("login", args);
	}
};

LoginManager loginManager(1234);

int main() {
	boost::asio::io_service io_service;
	ClientRepository repo(&io_service, "localhost", 6667, "simple_example.dc", "SimpleExample v0.2",
		[]{
			loginManager.sendLogin("guest", "guest");
			cout << "hello response" << endl;

		});

	repo.classRegister("LoginManager", &dclassInstantiateUD<LoginManager>, T_DOG);

	loginManager.setCR(&repo);

	repo.loop();
}
