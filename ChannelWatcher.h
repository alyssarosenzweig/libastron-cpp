#include "global.h"

class ChannelWatcher {
public:
	ChannelWatcher(uint64_t);
	virtual void message(Datagram dg, uint64_t sender, uint16_t msgtype);
protected:
	uint64_t m_channel;
}