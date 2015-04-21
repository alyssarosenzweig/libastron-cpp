#ifndef __DISTRIBUTED_OBJECT_H_
#define __DISTRIBUTED_OBJECT_H_

#include "ConnectionRepository.h"
#include "ChannelWatcher.h"
#include "msgtypes.h"

#include "AIRepository.h"

class DistributedObject : public ChannelWatcher {
public:
	DistributedObject(uint32_t do_id);
	DistributedObject();

	virtual string classname() {
		return "DistributedObject";
	}

	void message(ConnectionRepository* cr, DatagramIterator* dg, uint64_t sender, uint16_t msgtype);
	virtual bool fieldUpdate(string fieldName, vector<DValue> arguments) {
		cout << "Warning: Unhandled field update for DO; fieldname " << fieldName << endl;
		return false;
	};

	void setCR(ConnectionRepository* cr) {
		m_cr = cr;
	};

	void setDoId(uint32_t doId) {
		m_do_id = doId;
	};

	uint32_t getDoId() {
		return m_do_id;
	}

	void sendUpdate(string fieldName, vector<DValue>& arguments);

	void generateWithRequiredAndId(uint32_t doId, uint32_t parentId, uint32_t zoneId) {
		m_cr->generateWithRequiredAndId(this, doId, parentId, zoneId, vector<Method*> {});
	};

	void generateWithRequired(uint32_t parentId, uint32_t zoneId) {
		m_cr->generateWithRequired(this, parentId, zoneId, vector<Method*> {});
	};

	virtual vector<DValue> get(string field) {
		cout << "ERROR: override `get` for field " << field << " at " << classname() << "(" << m_do_id << ")" << endl;
		return vector<DValue>{};
	};
protected:
	ConnectionRepository* m_cr;
	uint32_t m_do_id;
};

#endif
