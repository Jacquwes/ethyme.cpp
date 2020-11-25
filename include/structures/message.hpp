#pragma once

#include "common.hpp"

#include "entity.hpp"
#include "user.hpp"

namespace Ethyme::Structures
{
	class Message : public Entity
	{
	public:
		Message(const nlohmann::json& data);

		std::shared_ptr<const Structures::User> Author() const;
		const std::string& Content() const;

	private:
		std::shared_ptr<const Structures::User> m_author;
		std::string m_content;
	};
}