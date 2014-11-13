#ifndef __CLIENT_REPOSITORY_H_
#define __CLIENT_REPOSITORY_H_

#include "global.h"
#include "ConnectionRepository.h"

class ClientRepository : public ConnectionRepository {
public:
	ClientRepository(boost::asio::io_service* io_service, 
					string host, 
					uint16_t port, 
					string dcFile,
					string version);
};

#endif