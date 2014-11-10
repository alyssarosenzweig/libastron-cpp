#include "Connection.h"

using boost::asio::ip::tcp;

Connection::Connection(string host, uint16_t port) : 
													m_host(host),
													m_port(port)
{
	cout << "Init connection at " << m_host << ":" << m_port << ".." << endl;

	// boost example
	// http://www.boost.org/doc/libs/1_42_0/doc/html/boost_asio/tutorial/tutdaytime1/src.html

	boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query(m_host, to_string(m_port));;
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    tcp::resolver::iterator end;

    tcp::socket socket(io_service);
    boost::system::error_code error = boost::asio::error::host_not_found;
    while (error && endpoint_iterator != end)
    {
      socket.close();
      socket.connect(*endpoint_iterator++, error);
    }
    if (error)
      throw boost::system::system_error(error);

}