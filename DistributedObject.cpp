#include "DistributedObject.h"

DistributedObject::DistributedObject(uint32_t do_id) : ChannelWatcher(do_id), m_do_id(do_id)
{

}

void DistributedObject::message(ConnectionRepository* cr, DatagramIterator* di, uint64_t sender, uint16_t msgtype)
{
	switch(msgtype) {
		case STATESERVER_OBJECT_SET_FIELD: {
			cout << "DistributedObject " << m_do_id << ": " << sender << " set field" << endl;
			uint32_t do_id = di->read_uint32();
			uint16_t field_id = di->read_uint16();

			cout << "Updating field " << field_id << " on DO " << do_id << endl;

			Module* module = cr->getModule();
			Field* field = module->field_by_id(field_id);
			Method* method = field->type()->as_method();

			for(int i = 0; i < method->num_parameters(); ++i) {
				Parameter* param = method->get_parameter(i);
				Type* ptype = param->type();

				if(ptype->subtype() == kTypeVarstring) {
					cout << di->read_string() << endl;
				} else {
					cout << "TODO: support actually reading type " << ptype->to_string() << endl;
				}
			}

			cout << "Field " << field->name() << method->to_string() << endl;
			break;
		}
		default:
		{
			cout << "DistributedObject " << m_do_id << ": " << sender << " sent an unknown msgtype " << msgtype << endl;
		}
	}
}