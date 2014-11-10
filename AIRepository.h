#ifndef __AI_REPOSITORY_H_
#define __AI_REPOSITORY_H_

#include "global.h"
#include "ConnectionRepository.h"

class AIRepository : public ConnectionRepository {
public:
	AIRepository(boost::asio::io_service* io_service,
				string host,
				uint16_t port,
				string dcFile);
};

#endif