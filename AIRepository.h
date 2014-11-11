#ifndef __AI_REPOSITORY_H_
#define __AI_REPOSITORY_H_

#include "global.h"
#include "ConnectionRepository.h"
#include "ChannelWatcher.h"

class AIRepository : public ConnectionRepository {
public:
	AIRepository(boost::asio::io_service* io_service,
				string host,
				uint16_t port,
				string dcFile,
				uint64_t channel,
				uint64_t stateserver);
	void internal_header(Datagram* dg, vector<uint64_t> recipients, uint64_t sender, uint16_t msgtype);
	void control_header(Datagram* dg, uint16_t msgtype);

	void subscribe_channel(ChannelWatcher* channel);
	void unsubscribe_channel(uint64_t channel);

	void set_client_state(uint64_t client, uint16_t state);

	uint64_t get_message_sender() {
		return m_message_sender;
	};

	void set_message_sender(uint64_t sender) {
		m_message_sender = sender;
	};

	void generateWithRequiredAndId(DistributedObject* obj, uint32_t doId, uint32_t parentId, uint32_t zoneId, vector<Method*> optionals);

private:
	void on_data(uint8_t* data, uint16_t len);

	map<uint64_t, ChannelWatcher*> m_watchers;
	uint64_t m_message_sender;
	uint64_t m_air_id;
	uint64_t m_stateserver;
};

#endif