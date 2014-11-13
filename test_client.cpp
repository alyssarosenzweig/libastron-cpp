#include <ClientRepository.h>
#include <DistributedObject.h>
#include <global.h>
#include <bamboo/module/Numeric.h>
#include <bamboo/module/NumericRange.h>
#include <bamboo/module/Array.h>

class LoginManager : public DistributedObject {
public:
	LoginManager(uint64_t do_id) : DistributedObject(do_id) {};
	string classname() { return "LoginManager"; };

	void sendLogin(string username, string password) {
		NumericRange* range = new NumericRange(0, 65535);
		Array* stringType = new Array(new Numeric(kTypeChar), *range);
		Value* username_ = new Value(stringType);
		Value* password_ = new Value(stringType);
		username_->string_ = username;
		password_->string_ = password;
		sendUpdate("login", vector<Value*>{username_, password_});
	}
};

LoginManager loginManager(1234);

int main() {
	boost::asio::io_service io_service;
	ClientRepository repo(&io_service, "localhost", 7198, "simple_example.dc", "SimpleExample v0.2", 
		[]{
			loginManager.sendLogin("guest", "guest");
			cout << "hello response" << endl;

		});

	repo.loop();
}