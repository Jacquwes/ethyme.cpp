#pragma once

#include "common.hpp"
#include "collections/collection.hpp"
#include "structures/entity.hpp"
#include "structures/mentions.hpp"
#include "structures/user.hpp"

namespace Ethyme
{
	class Client;
}

namespace Ethyme::Structures
{
	namespace Channels
	{
		class TextChannel;
	}

	/**
	 * @brief Represents a Discord Message.
	*/
	class Message : public Entity, public std::enable_shared_from_this<Message>
	{
	public:
		Message(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client);

		/**
		 * @brief The User who sent the Message
		*/
		std::shared_ptr<Structures::User> Author();
		/**
		 * @brief Channel where the Message was sent
		*/
		std::shared_ptr<Structures::Channels::TextChannel> Channel();
		/**
		 * @brief Content of the Message
		*/
		std::string const& Content() const;
		/**
		 * @brief Delete the Message
		*/
		cppcoro::task<std::shared_ptr<Message>> Delete();
		/**
		 * @brief Mentions included in the message.
		*/
		// Structures::Mentions const& Mentions() const;

	private:
		std::shared_ptr<Structures::User> m_author;
		std::shared_ptr<Structures::Channels::TextChannel> m_channel;
		std::string m_content;
		// Structures::Mentions m_mentions;

		// Collections::Collection<std::reference_wrapper<User>> m_channelsMentions;
		// Collections::Collection<std::reference_wrapper<User>> m_usersMentions;
	};
}