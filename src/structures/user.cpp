#include "structures/user.hpp"

namespace Ethyme::Structures
{
	const bool& User::Bot() const { return m_bot; }
	const std::string& User::Discriminator() const { return m_discriminator; }
	const std::string& User::Username() const { return m_username; }

	User::User(const nlohmann::json& data)
		: Entity(data["id"].get<std::string>())
		, m_bot(data["bot"].get<bool>())
		, m_discriminator(data["discriminator"].get<std::string>())
		, m_username(data["username"].get<std::string>())
	{}
}