#include "events/messagecreate.hpp"

namespace Ethyme::Events
{
	MessageCreate::MessageCreate(const nlohmann::json& data)
		: m_message(new Structures::Message(data))
	{}

	std::shared_ptr<const Structures::Message> MessageCreate::Message() const { return m_message; }
}