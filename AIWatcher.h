#ifndef __AI_WATCHER_H_
#define __AI_WATCHER_H_

#include "global.h"
#include "ChannelWatcher.h"

class AIWatcher : public ChannelWatcher {
public:
	AIWatcher(uint64_t airId) : ChannelWatcher(airId) {

	};

	void message(ConnectionRepository* cr, DatagramIterator* di, uint64_t sender, uint16_t msgtype) {
		cout << "AIWatcher message type " << msgtype << endl;

		switch(msgtype) {
			case STATESERVER_OBJECT_SET_FIELD: {
				//((AIRepository*) cr)->set_message_sender(sender);
				cr->handleSetField(di);
				break;
			};
		}
	}
};

#endif