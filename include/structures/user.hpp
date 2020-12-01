#pragma once

#include "common.hpp"
#include "entity.hpp"

namespace Ethyme
{
	class Client;
}

namespace Ethyme::Structures
{
	class User : public Entity
	{
	public:
		User(const nlohmann::json& data, const Ethyme::Client& client);

		const bool& Bot() const;
		const std::string& Discriminator() const;
		const std::string& Username() const;

	protected:
		bool m_bot;
		std::string m_discriminator;
		std::string m_username;
	};
}