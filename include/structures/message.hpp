#pragma once

#include "common.hpp"
#include "structures/entity.hpp"
#include "structures/user.hpp"

namespace Ethyme::Structures
{
	class TextChannel;

	class Message : public Entity
	{
	public:
		Message(const nlohmann::json& data, const Ethyme::Client& client);

		const Structures::User& Author() const;
		const Structures::TextChannel& Channel() const;
		const std::string& Content() const;

	private:
		Structures::User m_author;
		const Structures::TextChannel& m_channel;
		std::string m_content;
	};
}