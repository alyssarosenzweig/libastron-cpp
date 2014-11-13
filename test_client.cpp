#include <ClientRepository.h>
#include <DistributedObject.h>
#include <global.h>

class Varstring : public Type {
public:
	Varstring() : Type() {
		m_subtype = kTypeVarstring;
	}
};

class LoginManager : public DistributedObject {
public:
	LoginManager(uint64_t do_id) : DistributedObject(do_id) {};
	string classname() { return "LoginManager"; };

	void sendLogin(string username, string password) {
		Value* username_ = new Value(new Varstring());
		Value* password_ = new Value(new Varstring());

		username_->string_ = username;
		password_->string_ = password;

		sendUpdate("login", vector<Value*>{username_, password_});
	}
};

int main() {
	boost::asio::io_service io_service;
	ClientRepository repo(&io_service, "localhost", 7198, "simple_example.dc", "SimpleExample v0.2", 
		[]{
			cout << "hello response" << endl;
		});

	repo.loop();
}