#include "DistributedObject.h"
#include "AIRepository.h"

DistributedObject::DistributedObject(uint32_t do_id) : ChannelWatcher(do_id), m_do_id(do_id)
{

}

DistributedObject::DistributedObject() : ChannelWatcher(0), m_do_id(0)
{

}

void DistributedObject::message(ConnectionRepository* cr, DatagramIterator* di, uint64_t sender, uint16_t msgtype)
{
	switch(msgtype) {
		case STATESERVER_OBJECT_SET_FIELD: {
			if(sender)
				((AIRepository*) cr)->set_message_sender(sender);

			cr->handleSetField(di);

			break;
		}
		default:
		{
			cout << "DistributedObject " << m_do_id << ": " << sender << " sent an unknown msgtype " << msgtype << endl;
		}
	}
}

void DistributedObject::sendUpdate(string field, vector<DValue> arguments) {
	m_cr->sendUpdate(this, field, arguments);
}
