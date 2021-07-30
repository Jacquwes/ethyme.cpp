#include "events/messagecreate.hpp"

namespace Ethyme::Events
{
	MessageCreate::MessageCreate(std::shared_ptr<Structures::Message>& message)
		: m_message{ message }
	{}

	std::shared_ptr<Structures::Message>& MessageCreate::Message() { return m_message; }
}