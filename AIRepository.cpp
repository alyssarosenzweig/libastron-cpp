#include "AIRepository.h"

AIRepository::AIRepository(boost::asio::io_service* io_service,
				string host,
				uint16_t port,
				string dcFile) : ConnectionRepository(io_service, host, port, dcFile) {

}

void AIRepository::internal_header(Datagram dg, 
									vector<uint64_t> recipients, 
									uint64_t sender, 
									uint16_t msgtype)
{
	dg.write_uint8(recipients.size());

	for(uint64_t recipient : recipients) {
		dg.write_uint64(recipient);
	}

	dg.write_uint64(sender);

	dg.write_uint16(msgtype);
}

void AIRepository::control_header(Datagram dg, uint16_t msgtype) {
	// single recipient; channel 1
	dg.write_uint8(1);
	dg.write_uint64(1);

	dg.write_uint16(msgtype);
}