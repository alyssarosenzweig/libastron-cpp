#include "ClientRepository.h"

ClientRepository::ClientRepository(boost::asio::io_service* io_service, 
					string host, 
					uint16_t port, 
					string dcFile,
					string version) : ConnectionRepository(io_service, host, port, dcFile)
{

}