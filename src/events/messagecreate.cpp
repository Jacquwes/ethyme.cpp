#include "events/messagecreate.hpp"

namespace Ethyme::Events
{
	MessageCreate::MessageCreate(const nlohmann::json& data, const Ethyme::Client& client)
		: m_message(Structures::Message(data, client))
	{}

	Structures::Message& MessageCreate::Message() { return m_message; }
}