#include "AIRepository.h"
#include "msgtypes.h"
#include "DistributedObject.h"

AIRepository::AIRepository(boost::asio::io_service* io_service,
				string host,
				uint16_t port,
				string dcFile,
				uint64_t channel,
				uint64_t stateserver) : ConnectionRepository(io_service, host, port, dcFile),
									m_air_id(channel),
									m_stateserver(stateserver) {
	ChannelWatcher airWatcher(m_air_id);
	subscribe_channel(&airWatcher);
}

void AIRepository::internal_header(Datagram* dg, 
									vector<uint64_t> recipients, 
									uint64_t sender, 
									uint16_t msgtype)
{
	dg->add_uint8(recipients.size());

	for(uint64_t recipient : recipients) {
		dg->add_uint64(recipient);
	}

	dg->add_uint64(sender);

	dg->add_uint16(msgtype);
}

void AIRepository::control_header(Datagram* dg, uint16_t msgtype) {
	// single recipient; channel 1
	dg->add_uint8(1);
	dg->add_uint64(1);

	dg->add_uint16(msgtype);
}

void AIRepository::subscribe_channel(ChannelWatcher* channel) {
	Datagram dg;
	control_header(&dg, CONTROL_ADD_CHANNEL);
	dg.add_uint64(channel->getChannel());
	send(dg);

	m_watchers[channel->getChannel()] = channel;
}

void AIRepository::unsubscribe_channel(uint64_t channel) {
	Datagram dg;
	control_header(&dg, CONTROL_REMOVE_CHANNEL);
	dg.add_uint64(channel);
	send(dg);

	// FIXME: remove channel watcher
}

void AIRepository::set_client_state(uint64_t channel, uint16_t state) {
	Datagram dg;
	internal_header(&dg, vector<uint64_t>{channel}, m_air_id, CLIENTAGENT_SET_STATE);
	dg.add_uint16(state);
	send(dg);
}

void AIRepository::on_data(uint8_t* data, uint16_t len) {
    Datagram dg(data, len);
    DatagramIterator di(dg);

    uint8_t num_recipients = di.read_uint8();
    vector<uint64_t> recipients;

    while(num_recipients--) {
            uint64_t recipient = di.read_uint64();
            recipients.push_back(recipient);
    }

    uint64_t sender = di.read_uint64();
    uint16_t msgtype = di.read_uint16();

    for(uint64_t recipient : recipients) {
    	if(m_watchers.find(recipient) != m_watchers.end()) {
    		m_watchers[recipient]->message(this, &di, sender, msgtype);
    	} else {
    		cout << "No one is listening to " << recipient << endl;
    	}
    }
}

void AIRepository::generateWithRequiredAndId(
								DistributedObject* obj,
						 		uint32_t doId, 
						 		uint32_t parentId, uint32_t zoneId,
						 		vector<Method*> optionals)
{
	obj->setDoId(doId);
	cout << "generateWithRequiredAndId doId: " << doId << " (" << parentId << "," << zoneId << ")" << endl;

	Datagram dg;
	internal_header(&dg, vector<uint64_t>{m_stateserver}, m_air_id, STATESERVER_CREATE_OBJECT_WITH_REQUIRED);
	dg.add_uint32(doId);
	dg.add_uint32(parentId);
	dg.add_uint32(zoneId);
	dg.add_uint16(dclassId);
	addRequiredFields(&dg, obj);
	send(dg);
}