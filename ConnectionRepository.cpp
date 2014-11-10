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

void ConnectionRepository::on_data(uint8_t* data, uint16_t len) {
	printf("%d bytes received\n", len);
}

void ConnectionRepository::loop() {
	m_connection.poll(
		[&](uint8_t* data, uint16_t len) {
			printf("Hello from within the lambda!\n");
			on_data(data, len);
		}
	);
}