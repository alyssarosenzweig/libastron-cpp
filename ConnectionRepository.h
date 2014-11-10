#ifndef __CONNECTIONREPO_H__
#define __CONNECTIONREPO_H__

#include "global.h"
#include "Connection.h"

class ConnectionRepository {
public:
	ConnectionRepository(boost::asio::io_service* io_service, string m_host, uint16_t m_port, string dcFile);
	void send(Datagram dg);
	void close();
	void loop();
private:
	Module* m_module;
	Connection m_connection;

	string m_dcFile;
	string m_host;
	uint16_t m_port;

	void on_data(uint8_t* data, uint16_t len);
};

#endif