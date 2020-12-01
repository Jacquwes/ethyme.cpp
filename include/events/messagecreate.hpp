#pragma once

#include "../common.hpp"
#include "event.hpp"
#include "../structures/message.hpp"

namespace Ethyme
{
	class Client;
}

namespace Ethyme::Events
{
	class MessageCreate : public Event
	{
	public:
		MessageCreate(const nlohmann::json& data, const Ethyme::Client& client);

		const Structures::Message& Message() const;

	private:
		Structures::Message m_message;
	};
}