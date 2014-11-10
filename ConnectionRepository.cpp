#include "ConnectionRepository.h"

vector<string> astron_keywords {"clsend", "ownsend", "clrecv", "ownrecv",
                               "airecv", "broadcast", "ram", "required", "db"};

ConnectionRepository::ConnectionRepository(boost::asio::io_service* io_service, string host, uint16_t port, string dcFile) : 
												m_dcFile(dcFile),
												m_host(host),
												m_port(port),
												m_connection(Connection(io_service, host, port))
{
	cout << "Initializing ConnectionRepository with dcFile " << dcFile << endl;
	
	m_module = new Module();

	for(string keyword : astron_keywords) {
        m_module->add_keyword(keyword);
    }

    parse_dcfile(m_module, m_dcFile);
}

void ConnectionRepository::send(Datagram dg) {
	m_connection.send(dg);
}

void ConnectionRepository::close() {
	m_connection.close();
}