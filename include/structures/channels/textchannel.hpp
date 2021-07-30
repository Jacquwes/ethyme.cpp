#pragma once

#include "common.hpp"
#include "structures/channels/channel.hpp"

namespace Ethyme::Structures
{
	class Message;

	namespace Channels
	{
		/**
		 * @brief Represent all text channels.
		*/
		class TextChannel : public virtual Channel
		{
		public:
			TextChannel(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client);
			virtual ~TextChannel() = default;

			/**
			 * @brief Send a message to the channel.
			 * @param content Content of the message.
			*/
			cppcoro::task<std::shared_ptr<Message>> Send(std::string const& content) const;
		};
	}
}
