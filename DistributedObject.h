#ifndef __DISTRIBUTED_OBJECT_H_
#define __DISTRIBUTED_OBJECT_H_

#include "ChannelWatcher.h"

class DistributedObject : public ChannelWatcher {
public:
	DistributedObject(uint32_t do_id);
	void message(DatagramIterator dg, uint64_t sender, uint16_t msgtype);
private:
	uint32_t m_do_id;
};

#endif