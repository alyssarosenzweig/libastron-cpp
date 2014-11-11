#include "ConnectionRepository.h"
#include "DistributedObject.h"

vector<string> astron_keywords {"clsend", "ownsend", "clrecv", "ownrecv",
                               "airecv", "broadcast", "ram", "required", "db"};

ConnectionRepository::ConnectionRepository(boost::asio::io_service* io_service, string host, uint16_t port, string dcFile) : 
												m_dcFile(dcFile),
												m_host(host),
												m_port(port),
												m_connection(Connection(io_service, host, port))
{
	cout << "Initializing ConnectionRepository with dcFile " << dcFile << endl;
	
	m_module = new Module();

	for(string keyword : astron_keywords) {
        m_module->add_keyword(keyword);
    }

    parse_dcfile(m_module, m_dcFile);
}

void ConnectionRepository::send(Datagram dg) {
	m_connection.send(dg);
}

void ConnectionRepository::close() {
	m_connection.close();
}

void ConnectionRepository::on_data(uint8_t* data, uint16_t len) {
}

void ConnectionRepository::loop() {
	m_connection.poll(
		[&](uint8_t* data, uint16_t len) {
			on_data(data, len);
		}
	);
}

void ConnectionRepository::addRequiredFields(Datagram* dg, DistributedObject* obj) {

}

void ConnectionRepository::handleSetField(DatagramIterator* di) {
	uint32_t do_id = di->read_uint32();
	uint16_t field_id = di->read_uint16();

	Module* module = getModule();
	Field* field = module->field_by_id(field_id);
	Type* fieldType = field->type();
	Method* method = field->type()->as_method();

	vector<Value*> arguments;
	arguments.reserve(method->num_parameters());

	for(int i = 0; i < method->num_parameters(); ++i) {
		Parameter* param = method->get_parameter(i);
		Type* ptype = param->type();
		Value val(ptype);

		if(ptype->subtype() == kTypeVarstring) {
			val.string_ = di->read_string();
		} else {
			cout << "TODO: support actually reading type " << ptype->to_string() << endl;
		}

		arguments.push_back(&val);
	}

	DistributedObject* distObj = NULL; // TODO: maintain doId2do tables

	if(!distObj->fieldUpdate(field->name(), arguments)) {
		cout << "Warning: unhandled field update for doId " << do_id << " field name " << field->name() << endl;
	}
}