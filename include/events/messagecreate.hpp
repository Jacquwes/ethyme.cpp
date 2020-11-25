#pragma once

#include "../common.hpp"
#include "event.hpp"
#include "../structures/message.hpp"

namespace Ethyme::Events
{
	class MessageCreate : public Event
	{
	public:
		MessageCreate(const nlohmann::json& data);

		std::shared_ptr<const Structures::Message> Message() const;

	private:
		std::shared_ptr<const Structures::Message> m_message;
	};
}