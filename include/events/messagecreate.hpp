#pragma once

#include "../common.hpp"
#include "event.hpp"
#include "../structures/message.hpp"

DefineClient

namespace Ethyme::Events
{
	class MessageCreate : public Event
	{
	public:
		MessageCreate(const nlohmann::json& data, Client_);

		std::shared_ptr<const Structures::Message> Message() const;

	private:
		std::shared_ptr<const Structures::Message> m_message;
	};
}