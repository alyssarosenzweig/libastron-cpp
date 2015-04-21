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
	Class* dclass = m_module->class_by_name(obj->classname());

	for(int i = 0; i < dclass->num_fields(); ++i) {
		Field* field = dclass->get_field(i);

		if(field->has_keyword("required")) {
			vector<DValue> arguments = obj->get(field->name());
			for(DValue argument : arguments) {
        addDatagramDValue(dg, argument);
			}
		}
	}
}

void ConnectionRepository::handleSetField(DatagramIterator* di) {
	uint32_t do_id = di->read_uint32();
	uint16_t field_id = di->read_uint16();

	Module* module = getModule();
	Field* field = module->field_by_id(field_id);
	Type* fieldType = field->type();
	Method* method = field->type()->as_method();

	vector<DValue> arguments;
	arguments.reserve(method->num_parameters());

	for(int i = 0; i < method->num_parameters(); ++i) {
		Parameter* param = method->get_parameter(i);
		Type* ptype = param->type();
		DValue v;

		if(ptype->subtype() == kTypeVarstring) {
			string s = di->read_string();
			v = $(s);
		} else if(ptype->subtype() == kTypeUint64) {
      v = duint64(di->read_uint64());
		} else {
			cout << "TODO: support actually reading type " << ptype->to_string() << endl;
		}

    dprint(v);

		arguments.push_back(v);
	}

	DistributedObject* distObj = m_doId2do[do_id];

	if(!distObj->fieldUpdate(field->name(), &arguments)) {
		cout << "Warning: unhandled field update for doId " << do_id << " field name " << field->name() << endl;
	}
}

void ConnectionRepository::addDatagramDValue(Datagram* dg, DValue v) {
  switch(v.d_type) {
    case d_uint8:
      dg->add_uint8(v.v_uint);
      break;
    case d_uint16:
      dg->add_uint16(v.v_uint);
      break;
    case d_uint32:
      dg->add_uint32(v.v_uint);
      break;
    case d_uint64:
      dg->add_uint64(v.v_uint);
      break;
    case d_int8:
      dg->add_int8(v.v_int);
      break;
    case d_int16:
      dg->add_int16(v.v_int);
      break;
    case d_int32:
      dg->add_int32(v.v_int);
      break;
    case d_int64:
      dg->add_int64(v.v_int);
      break;
    case d_float32:
      dg->add_float32(v.v_double);
      break;
    case d_string:
      dg->add_string(v.v_string);
      break;
    default:
      cout << "Attempting to add an unknown value of type " << v.d_type << endl;
      dprint(v);
      break;
  }
}

void ConnectionRepository::registerDOG(DistributedObject* dog) {
	m_doId2do[dog->getDoId()] = dog;
}
