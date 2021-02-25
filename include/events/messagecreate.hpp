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
	/**
	 * @brief Event triggered when the Client receives a message.
	*/
	class MessageCreate : public Event
	{
	public:
		/**
		 * @brief Event's constructor
		 * @param data Raw event data
		 * @param client Client's instance
		*/
		MessageCreate(const nlohmann::json& data, const Ethyme::Client& client);

		/**
		 * @brief Message
		 * @return Message received by the Client
		*/
		Structures::Message& Message();

	private:
		Structures::Message m_message;
	};
}