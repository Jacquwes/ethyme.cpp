#include "structures/user.hpp"

namespace Ethyme::Structures
{
	const bool& User::Bot() const { return m_bot; }
	const std::string& User::Discriminator() const { return m_discriminator; }
	const std::string& User::Username() const { return m_username; }

	User::User(const nlohmann::json& data, const std::shared_ptr<Ethyme::Client>& client)
		: Entity(data["id"], client)
		, m_bot(data["bot"])
		, m_discriminator(data["discriminator"])
		, m_username(data["username"])
	{}
}