#ifndef __CLIENT_REPOSITORY_H_
#define __CLIENT_REPOSITORY_H_

#include "global.h"
#include "ConnectionRepository.h"
#include "client_msgtypes.h"

class ClientRepository : public ConnectionRepository {
public:
	ClientRepository(boost::asio::io_service* io_service,
					string host,
					uint16_t port,
					string dcFile,
					string version,
					function<void()> helloResp);
	void client_header(Datagram* dg, uint16_t msgtype);
	void sendHello();
	void sendUpdate(DistributedObject* obj, string field, vector<DValue> arguments);
private:
	void on_data(uint8_t* data, uint16_t len);

	string m_version;
	function<void()> m_helloResp;
};

#endif
