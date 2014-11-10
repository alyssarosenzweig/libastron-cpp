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
	void internal_header(Datagram dg, vector<uint64_t> recipients, uint64_t sender, uint16_t msgtype);
	void control_header(Datagram dg, uint16_t msgtype);
};

#endif