#include "events/messagecreate.hpp"

namespace Ethyme::Events
{
	MessageCreate::MessageCreate(Structures::Message& message)
		: m_message{ message }
	{}

	Structures::Message& MessageCreate::Message() { return m_message; }
}