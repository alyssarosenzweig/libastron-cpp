#ifndef __AI_WATCHER_H_
#define __AI_WATCHER_H_

#include "global.h"
#include "ChannelWatcher.h"

class AIRepository;

class AIWatcher : public ChannelWatcher {
public:
	AIWatcher(uint64_t airId) : ChannelWatcher(airId) {

	};

	void message(AIRepository* cr, DatagramIterator* di, uint64_t sender, uint16_t msgtype);
};

#endif