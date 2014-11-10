#include "AIRepository.h"

AIRepository::AIRepository(boost::asio::io_service* io_service,
				string host,
				uint16_t port,
				string dcFile) : ConnectionRepository(io_service, host, port, dcFile) {

}