#include "global.h"

#include <boost/asio.hpp>

class Connection {
public:
	Connection(boost::asio::io_service* io_service, string host, uint16_t port);
	void send(Datagram dg);
	void close();
	void poll();
private:
	string m_host;
	uint16_t m_port;
	shared_ptr<boost::asio::ip::tcp::socket> m_socket;
};