ChannelWatcher::ChannelWatcher(uint64_t channel) : m_channel(channel)
{

}

void ChannelWatcher::message(Datagram dg, uint64_t sender, uint16_t msgtype)
{
	cout << sender << " sent " << msgtype << " to me, ChannelWatcher " << m_channel;
}