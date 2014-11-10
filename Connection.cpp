#include "Connection.h"

Connection::Connection(string host, uint16_t port) : 
													m_host(host),
													m_port(port)
{
	cout << "Init connection.." << endl;
}