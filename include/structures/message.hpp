#pragma once

#include "common.hpp"
#include "structures/collection.hpp"
#include "structures/entity.hpp"
#include "structures/mentions.hpp"
#include "structures/user.hpp"

namespace Ethyme::Structures
{
	class TextChannel;

	/**
	 * @brief Represents a Discord Message.
	*/
	class Message : public Entity
	{
	public:
		Message(nlohmann::json const& data, Ethyme::Client const& client);

		/**
		 * @brief The User who sent the Message
		*/
		Structures::User const& Author() const;
		/**
		 * @brief Channel where the Message was sent
		*/
		Structures::TextChannel const& Channel() const;
		/**
		 * @brief Content of the Message
		*/
		std::string const& Content() const;
		/**
		 * @brief Mentions included in the message.
		*/
		Structures::Mentions const& Mentions() const;

	private:
		Structures::User m_author;
		Structures::TextChannel const& m_channel;
		std::string m_content;
		Structures::Mentions m_mentions;

		Collection<std::shared_ptr<Structures::Channel>> m_channelsMentions;
		Collection<std::shared_ptr<User>> m_usersMentions;
	};
}