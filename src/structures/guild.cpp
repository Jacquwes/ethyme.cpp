#include "structures/guild.hpp"

#include "client.hpp"
#include "structures/channels/textchannel.hpp"
#include "structures/member.hpp"
#include "structures/role.hpp"

namespace Ethyme::Structures
{
	Guild::Guild(nlohmann::json const& data, Ethyme::Client const& client)
		: Entity(data["id"].get<std::string>(), client)
		, m_channels{ client, Constants::API::Channels }
		, m_members{ client, Constants::API::Guilds + Id().ToString() + "/members/" }
		, m_name{ data["name"].get<std::string>() }
		, m_roles{ client, Constants::API::Guilds + Id().ToString() + "/roles/" }
		, m_ownerId{ data["owner_id"].get<std::string>() }
	{}

	Collections::Collection<std::reference_wrapper<Channel>> const& Guild::Channels() const { return m_channels; }
	Collections::Collection<Member> const& Guild::Members() const { return m_members; }
	std::string const& Guild::Name() const { return m_name; }
	Member const& Guild::Owner() const { return *m_members.FindById(m_ownerId); }
	Collections::Collection<Role> const& Guild::Roles() const { return m_roles; }
}