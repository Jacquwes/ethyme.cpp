#pragma once

#include "common.hpp"
#include "structures/channels/channel.hpp"

namespace Ethyme::Structures
{
	/**
	 * @brief Represent all text channels.
	*/
	class TextChannel : public Channel
	{
	public:
		TextChannel(const nlohmann::json& data, const Ethyme::Client& client);

		/**
		 * @brief Send a message to the channel.
		 * @param content Content of the message.
		*/
		void Send(const std::string& content) const;
	};
}
