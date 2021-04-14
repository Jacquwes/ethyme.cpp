#include "structures/guild.hpp"

#include "client.hpp"
#include "structures/channels/channel.hpp"
#include "structures/channels/textchannel.hpp"
#include "structures/member.hpp"
#include "structures/role.hpp"

namespace Ethyme::Structures
{
	Guild::Guild(nlohmann::json const& data, Ethyme::Client& client)
		: Entity(data["id"].get<std::string>(), client)
		, m_channels{ client, Constants::API::Channels }
		, m_members{ client, Constants::API::Guilds + Id().ToString() + "/members/" }
		, m_name{ data["name"].get<std::string>() }
		, m_roles{ client, Constants::API::Guilds + Id().ToString() + "/roles/" }
		, m_ownerId{ data["owner_id"].get<std::string>() }
	{
		for (auto& role : data["roles"])
			m_roles.Add(Role(role, client));
		for (auto& channel : data["channels"])
			switch (channel["type"].get<Channels::Channel::ChannelType>())
			{
			case Channels::Channel::ChannelType::DirectMessage:
			case Channels::Channel::ChannelType::GroupDirectMessage:
			case Channels::Channel::ChannelType::GuildText:
			case Channels::Channel::ChannelType::GuildNews:
				m_channels.Add(
					Client().Channels().Add(Channels::TextChannel(channel, client))
				);
				break;
			default:
				break;
			}
	}

	Collections::Collection<std::reference_wrapper<Channels::Channel>>& Guild::Channels() { return m_channels; }
	Collections::Collection<Member>& Guild::Members() { return m_members; }
	std::string const& Guild::Name() const { return m_name; }
	Member& Guild::Owner() { return *m_members.FindById(m_ownerId); }
	Collections::Collection<Role>& Guild::Roles() { return m_roles; }
}