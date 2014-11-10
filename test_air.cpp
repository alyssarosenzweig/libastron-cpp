#include <bamboo/wire/Datagram.h>
#include <AIRepository.h>

int main() {
	boost::asio::io_service io_service;
	AIRepository repo(&io_service, "localhost", 7199, "simple_example.dc");

	Datagram dg;
	dg.add_uint8(1);
	dg.add_uint64(1);
	dg.add_uint16(9012);
	dg.add_string("libastron-c++");
	repo.send(dg);

	repo.close();
}