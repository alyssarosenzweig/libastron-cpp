#include "global.h"

#include <boost/asio.hpp>

class Connection {
public:
	Connection(string host, uint16_t port);
private:
	string m_host;
	uint16_t m_port;
};