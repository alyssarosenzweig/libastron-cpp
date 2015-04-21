#ifndef __CONNECTIONREPO_H__
#define __CONNECTIONREPO_H__

#include "global.h"
#include "Connection.h"
#include "DValue.hpp"

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
	void generateWithRequired(DistributedObject* obj, uint32_t parentId, uint32_t zone, vector<Method*> optionals) {
		generateWithRequiredAndId(obj, allocate_doId(), parentId, zone, optionals);
	}

	uint32_t allocate_doId() {
		return doId_counter++;
	}

	void addRequiredFields(Datagram* dg, DistributedObject* obj);
	virtual void sendUpdate(DistributedObject* obj, string field, vector<DValue>& arguments) {
		cout << "sendUpdate on " << field << endl;
	};
	void addDatagramDValue(Datagram* dg, DValue v);
	void handleSetField(DatagramIterator* dg);

	void registerDOG(DistributedObject* dog);

protected:
	Module* m_module;
	Connection m_connection;

	string m_dcFile;
	string m_host;
	uint16_t m_port;

	uint32_t doId_counter = 100000;

	virtual void on_data(uint8_t* data, uint16_t len);

	map<uint32_t, DistributedObject*> m_doId2do;
};

#endif
