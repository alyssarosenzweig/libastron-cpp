#ifndef __CONNECTIONREPO_H__
#define __CONNECTIONREPO_H__

#include "global.h"
#include "Connection.h"

class DistributedObject;

class ConnectionRepository {
public:
	ConnectionRepository(boost::asio::io_service* io_service, string m_host, uint16_t m_port, string dcFile);
	void send(Datagram dg);
	void close();
	void loop();

	Module* getModule() {
		return m_module;
	};

	virtual void generateWithRequiredAndId(DistributedObject* obj, uint32_t doId, uint32_t parentId, uint32_t zoneId, vector<Method*> optionals) {};
	void addRequiredFields(Datagram* dg, DistributedObject* obj);
	virtual void sendUpdate(DistributedObject* obj, string field, vector<Value*> arguments) {};

protected:
	Module* m_module;
	Connection m_connection;

	string m_dcFile;
	string m_host;
	uint16_t m_port;

	virtual void on_data(uint8_t* data, uint16_t len);
};

#endif