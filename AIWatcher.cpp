#include "AIWatcher.h"
#include "AIRepository.h"
#include "msgtypes.h"

void AIWatcher::message(ConnectionRepository* _cr, DatagramIterator* di, uint64_t sender, uint16_t msgtype) {
	cout << "AIWatcher message type " << msgtype << endl;

	AIRepository* cr = (AIRepository*) _cr;

	switch(msgtype) {
		case STATESERVER_OBJECT_SET_FIELD: {
			cr->set_message_sender(sender);
			cr->handleSetField(di);
			break;
		};
		case STATESERVER_OBJECT_ENTER_AI_WITH_REQUIRED: {
			cr->handleEnterObject(DatagramIterator* di, false, false, true);
			break;
		}
	}
}
