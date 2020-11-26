#pragma once

#include "common.hpp"

#include "entity.hpp"
#include "user.hpp"

DefineClient

namespace Ethyme::Structures
{
	class Channel;
	class TextChannel;

	class Message : public Entity, public std::enable_shared_from_this<Message>
	{
	public:
		Message(const nlohmann::json& data, const std::shared_ptr<Ethyme::Client>& client);

		const std::shared_ptr<Structures::User>& Author() const;
		const std::shared_ptr<const Structures::TextChannel>& Channel() const;
		const std::string& Content() const;

	private:
		std::shared_ptr<Structures::User> m_author;
		std::shared_ptr<const Structures::TextChannel> m_channel;
		std::string m_content;
	};
}