#include <ConnectionRepository.h>

int main() {
	boost::asio::io_service io_service;
	ConnectionRepository repo(&io_service, "localhost", 7199, "simple_example.dc");
}