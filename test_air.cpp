#include <bamboo/wire/Datagram.h>
#include <AIRepository.h>
#include <msgtypes.h>

int main() {
	boost::asio::io_service io_service;
	AIRepository repo(&io_service, "localhost", 7199, "simple_example.dc");

	Datagram dg;
	repo.control_header(&dg, CONTROL_SET_CON_NAME);
	dg.add_string("libastron-c++");
	repo.send(dg);

	repo.subscribe_channel(1234);

	repo.loop();
}