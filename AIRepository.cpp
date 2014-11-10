#include "AIRepository.h"
#include "msgtypes.h"

AIRepository::AIRepository(boost::asio::io_service* io_service,
				string host,
				uint16_t port,
				string dcFile) : ConnectionRepository(io_service, host, port, dcFile) {

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

void AIRepository::subscribe_channel(uint64_t channel) {
	Datagram dg;
	control_header(&dg, CONTROL_ADD_CHANNEL);
	dg.add_uint64(channel);
	send(dg);
}

void AIRepository::unsubscribe_channel(uint64_t channel) {
	Datagram dg;
	control_header(&dg, CONTROL_REMOVE_CHANNEL);
	dg.add_uint64(channel);
	send(dg);
}