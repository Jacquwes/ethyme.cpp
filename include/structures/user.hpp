#pragma once

#include "common.hpp"
#include "entity.hpp"

namespace Ethyme
{
	class Client;
}

namespace Ethyme::Structures
{
	/**
	 * @brief Represents a Discord User
	*/
	class User : public Entity
	{
	public:
		User(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client);

		bool const& Bot() const;
		std::string const& Discriminator() const;
		std::string const& Username() const;

		/**
		 * @brief Return the tag of the User
		*/
		operator const std::string() const&;

	protected:
		bool m_bot;
		std::string m_discriminator;
		std::string m_username;
	};
}