#include "structures/user.hpp"

#include "client.hpp"

namespace Ethyme::Structures
{
	const bool& User::Bot() const { return m_bot; }
	const std::string& User::Discriminator() const { return m_discriminator; }
	const std::string& User::Username() const { return m_username; }

	User::operator const std::string() const& { return m_username + "#" + m_discriminator; }

	User::User(const nlohmann::json& data, const Ethyme::Client& client)
		: Entity(data["id"], client)
		, m_bot(data.contains("bot") ? data["bot"].get<bool>() : false)
		, m_discriminator(data["discriminator"])
		, m_username(data["username"])
	{}
}