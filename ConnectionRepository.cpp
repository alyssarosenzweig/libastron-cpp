#include "ConnectionRepository.h"

vector<string> astron_keywords {"clsend", "ownsend", "clrecv", "ownrecv",
                               "airecv", "broadcast", "ram", "required", "db"};

ConnectionRepository::ConnectionRepository(string host, uint16_t port, string dcFile) : 
												m_dcFile(dcFile),
												m_host(host),
												m_port(port),
												m_connection(Connection(m_host, m_port))
{
	cout << "Initializing ConnectionRepository with dcFile " << dcFile << endl;
	
	m_module = new Module();

	for(string keyword : astron_keywords) {
        m_module->add_keyword(keyword);
    }

    parse_dcfile(m_module, m_dcFile);
}