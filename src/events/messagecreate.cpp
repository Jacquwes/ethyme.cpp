#include "events/messagecreate.hpp"

namespace Ethyme::Events
{
	MessageCreate::MessageCreate(const nlohmann::json& data, const Ethyme::Client& client)
		: m_message(Structures::Message(data, client))
	{}

	const Structures::Message& MessageCreate::Message() const { return m_message; }
}