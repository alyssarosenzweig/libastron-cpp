#include <ClientRepository.h>

int main() {
	boost::asio::io_service io_service;
	ClientRepository repo(&io_service, "localhost", 7199, "simple_example.dc", "SimpleExample v0.2");

	repo.loop();
}