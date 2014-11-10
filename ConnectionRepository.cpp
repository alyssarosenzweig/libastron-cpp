#include "ConnectionRepository.h"

vector<string> astron_keywords {"clsend", "ownsend", "clrecv", "ownrecv",
                               "airecv", "broadcast", "ram", "required", "db"};

ConnectionRepository::ConnectionRepository(string dcFile) : 
												m_dcFile(dcFile),
												m_connection(Connection("127.0.0.1", 7199))
{
	cout << "Initializing ConnectionRepository with dcFile " << dcFile << endl;
	
	m_module = new Module();

	for(string keyword : astron_keywords) {
        m_module->add_keyword(keyword);
    }

    parse_dcfile(m_module, m_dcFile);
}