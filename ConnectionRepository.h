#ifndef __CONNECTIONREPO_H__
#define __CONNECTIONREPO_H__

#include "global.h"
#include "Connection.h"

class ConnectionRepository {
public:
	ConnectionRepository(boost::asio::io_service* io_service, string m_host, uint16_t m_port, string dcFile);
	Connection m_connection;
private:
	Module* m_module;

	string m_dcFile;
	string m_host;
	uint16_t m_port;
};

#endif