#include "DistributedObject.h"

DistributedObject::DistributedObject(uint32_t do_id) : ChannelWatcher(do_id), m_do_id(do_id)
{

}

void DistributedObject::message(DatagramIterator dg, uint64_t sender, uint16_t msgtype)
{
	cout << sender << " sent " << msgtype << " to me, DistributedObject " << m_channel << endl;
}