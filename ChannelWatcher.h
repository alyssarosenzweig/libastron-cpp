#ifndef __CHANNEL_WATCHER_H_
#define __CHANNEL_WATCHER_H_

#include "global.h"
#include "ConnectionRepository.h"

class ChannelWatcher {
public:
	ChannelWatcher(uint64_t);
	virtual void message(ConnectionRepository* cr, DatagramIterator* dg, uint64_t sender, uint16_t msgtype);

	uint64_t getChannel() {
		return m_channel;
	}
protected:
	uint64_t m_channel;
};

#endif