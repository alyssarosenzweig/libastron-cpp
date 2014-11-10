#include <bamboo/wire/Datagram.h>
#include <AIRepository.h>

int main() {
	boost::asio::io_service io_service;
	AIRepository repo(&io_service, "localhost", 7199, "simple_example.dc");

	Datagram dg;
	repo.control_header(dg, 9012);
	dg.add_string("libastron-c++");
	repo.send(dg);

	repo.close();
}