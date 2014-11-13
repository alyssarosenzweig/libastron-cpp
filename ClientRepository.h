#ifndef __CLIENT_REPOSITORY_H_
#define __CLIENT_REPOSITORY_H_

#include "global.h"

class ClientRepository : public ConnectionRepository {
public:
	ClientRepository(boost::asio::io_service* io_service, 
					string m_host, 
					uint16_t m_port, 
					string dcFile,
					string version);
};

#endif