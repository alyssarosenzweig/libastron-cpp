#ifndef __CONNECTIONREPO_H__
#define __CONNECTIONREPO_H__

#include "global.h"
#include "Connection.h"

class ConnectionRepository {
public:
	ConnectionRepository(string m_host, uint16_t m_port, string dcFile);
private:
	Module* m_module;
	Connection m_connection;

	string m_dcFile;
	string m_host;
	uint16_t m_port;
};

#endif