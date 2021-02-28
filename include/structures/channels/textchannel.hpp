#pragma once

#include "common.hpp"
#include "structures/channels/channel.hpp"

namespace Ethyme::Structures
{
	class Message;

	/**
	 * @brief Represent all text channels.
	*/
	class TextChannel : public Channel
	{
	public:
		TextChannel(nlohmann::json const& data, Ethyme::Client& client);

		/**
		 * @brief Send a message to the channel.
		 * @param content Content of the message.
		*/
		cppcoro::task<Message> Send(std::string const& content) const;
	};
}
