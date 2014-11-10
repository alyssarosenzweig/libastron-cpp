#include <bamboo/wire/Datagram.h>
#include <ConnectionRepository.h>

int main() {
	boost::asio::io_service io_service;
	ConnectionRepository repo(&io_service, "localhost", 7199, "simple_example.dc");

	Datagram dg;
	dg.add_string("shadowcoder");
	repo.m_connection.send(dg);
}