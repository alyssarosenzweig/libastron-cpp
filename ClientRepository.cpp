#include "ClientRepository.h"

ClientRepository::ClientRepository(boost::asio::io_service* io_service, 
					string m_host, 
					uint16_t m_port, 
					string dcFile,
					string version) : ConnectionRepository(io_service, host, port, dcFile)
{

}