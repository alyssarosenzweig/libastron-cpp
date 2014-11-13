#include "ClientRepository.h"

ClientRepository::ClientRepository(boost::asio::io_service* io_service, 
					string host, 
					uint16_t port, 
					string dcFile,
					string version) : ConnectionRepository(io_service, host, port, dcFile),
										m_version(version)
{

}

void ClientRepository::sendHello() {
	uint32_t hash = 0xDEADBEEF;

	Datagram dg;
	client_header(&dg, CLIENT_HELLO);
	dg.add_string(m_version);
	dg.add_uint32(hash);
	send(dg);
}