#include "structures/user.hpp"

#include "client.hpp"

namespace Ethyme::Structures
{
	bool const& User::Bot() const { return m_bot; }
	std::string const& User::Discriminator() const { return m_discriminator; }
	std::string const& User::Username() const { return m_username; }

	User::operator const std::string() const& { return m_username + "#" + m_discriminator; }

	User::User(nlohmann::json const& data, Ethyme::Client& client)
		: Entity(data["id"], client)
		, m_bot(data.contains("bot") ? data["bot"].get<bool>() : false)
		, m_discriminator(data["discriminator"])
		, m_username(data["username"])
	{}
}