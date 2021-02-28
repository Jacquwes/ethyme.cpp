#include "structures/member.hpp"

#include "client.hpp"
#include "structures/role.hpp"

namespace Ethyme::Structures
{
	Member::Member(nlohmann::json const& data, Ethyme::Client& client)
		: Entity(data["id"].get<std::string>(), client)
		, m_nickname{ data.contains("nick") ? std::optional(data["nick"].get<std::string>()) : std::nullopt }
		, m_roles{ client }
		, m_user{ *client.Users().FindById(data["user"]["id"].get<std::string>()) }
	{}

	std::optional<std::string> const& Member::Nickname() const { return m_nickname; }
	Collections::Collection<std::reference_wrapper<Role>>& Member::Roles() { return m_roles; }
	Structures::User& Member::User() { return m_user; }
}