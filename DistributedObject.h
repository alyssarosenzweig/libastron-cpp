#ifndef __DISTRIBUTED_OBJECT_H_
#define __DISTRIBUTED_OBJECT_H_

#include "ConnectionRepository.h"
#include "ChannelWatcher.h"
#include "msgtypes.h"

class DistributedObject : public ChannelWatcher {
public:
	DistributedObject(uint32_t do_id);
	void message(ConnectionRepository* cr, DatagramIterator* dg, uint64_t sender, uint16_t msgtype);
	virtual bool fieldUpdate(string fieldName, vector<Value*> arguments) {
		return false;
	};

	void setCR(ConnectionRepository* cr) {
		m_cr = cr;
	};
protected:
	ConnectionRepository* m_cr;
	uint32_t m_do_id;
};

#endif