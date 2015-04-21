#include "ClientRepository.h"
#include "DistributedObject.h"

ClientRepository::ClientRepository(boost::asio::io_service* io_service,
					string host,
					uint16_t port,
					string dcFile,
					string version,
					function<void()> helloResp) : ConnectionRepository(io_service, host, port, dcFile),
										m_version(version),
										m_helloResp(helloResp)
{
	sendHello();
}

void ClientRepository::client_header(Datagram* dg, uint16_t msgtype) {
	dg->add_uint16(msgtype);
}

void ClientRepository::sendHello() {
	//uint32_t hash = m_module->hash(); // bug @kestred to implement
	uint32_t hash = 0xDEADBEEF;

	Datagram dg;
	client_header(&dg, CLIENT_HELLO);
	dg.add_uint32(hash);
	dg.add_string(m_version);
	send(dg);
}

void ClientRepository::on_data(uint8_t* data, uint16_t len) {
	cout << "Incoming data of len " << len << endl;

	Datagram dg(data, len);
    DatagramIterator di(dg);

    uint16_t msgtype = di.read_uint16();

    switch(msgtype) {
    	case CLIENT_EJECT: {
    		uint16_t errorCode = di.read_uint16();
    		string reason = di.read_string();

	    	cout << "Ejected (error code " << errorCode << ") " << reason << endl;

	    	exit(0); // boost is going to crash inevitably soon; quit now for a clearer error message
	    	break;
    	};
    	case CLIENT_HELLO_RESP: {
    		cout << "CLIENT_HELLO_RESP" << endl;
    		m_helloResp();
    		break;
    	};
    	default: {
    		cout << "Unknown client message: " << msgtype << endl;
    		break;
    	}
    }
}

void ClientRepository::sendUpdate(DistributedObject* obj, string fieldName, vector<DValue> arguments) {
	Class* dclass = m_module->class_by_name(obj->classname());
	Field* field = dclass->field_by_name(fieldName);
	uint16_t fieldId = field->id();

	Datagram dg;
	client_header(&dg, CLIENT_OBJECT_SET_FIELD);
	dg.add_uint32(obj->getDoId());
	dg.add_uint16(fieldId);

	for(DValue argument : arguments) {
		addDatagramDValue(&dg, argument);
	}


	send(dg);
}
