#include "structures/guild.hpp"

#include "client.hpp"
#include "structures/channels/channel.hpp"
#include "structures/channels/directmessage.hpp"
#include "structures/channels/groupdirectmessage.hpp"
#include "structures/channels/guildcategory.hpp"
#include "structures/channels/guildnews.hpp"
#include "structures/channels/guildstore.hpp"
#include "structures/channels/guildtext.hpp"
#include "structures/channels/guildvoice.hpp"
#include "structures/member.hpp"
#include "structures/role.hpp"

namespace Ethyme::Structures
{
	Guild::Guild(nlohmann::json const& data, Ethyme::Client& client, bool const& parse)
		: Entity(data["id"].get<std::string>(), client, !parse, data)
		, m_channels{ client, Constants::API::Channels }
		, m_members{ client, Constants::API::Guilds + Id().ToString() + "/members/" }
		, m_name{ data["name"].get<std::string>() }
		, m_roles{ client, Constants::API::Guilds + Id().ToString() + "/roles/" }
		, m_ownerId{ data["owner_id"].get<std::string>() }
	{
		if (parse) [[unlikely]]
			Parse(data);
	}

	Collections::Collection<Channels::Channel, true>& Guild::Channels() { return m_channels; }
	Collections::Collection<Member>& Guild::Members() { return m_members; }
	std::string const& Guild::Name() const { return m_name; }
	Member& Guild::Owner() { return *m_members.FindById(m_ownerId); }
	Collections::Collection<Role>& Guild::Roles() { return m_roles; }

	void Guild::Parse(nlohmann::json const& data)
	{

		if (!data.is_null()) [[unlikely]]
			Data()[0] = data;

		// sort channels, we need categories to be parsed first
		// because discord decided they'd send them in a random order
		std::vector<nlohmann::json> channels(Data()[0]["channels"].begin(), Data()[0]["channels"].end());
		std::ranges::sort(channels, [](nlohmann::json a, nlohmann::json b)
			{
				return a["type"] == Structures::Channels::Channel::ChannelType::GuildCategory;
			});

		for (auto& role : Data()[0]["roles"])
			m_roles.Add(Role(role, Client()));
		for (auto& channel : channels)
		{
			if (!channel.contains("guild_id"))
				const_cast<nlohmann::json&>(channel)["guild_id"] = Data()[0]["id"].get<std::string>();
			switch (channel["type"].get<Channels::Channel::ChannelType>())
			{
			case Channels::Channel::ChannelType::DirectMessage:
				m_channels.Add
				(
					Client().Channels().Add(Channels::DirectMessage(channel, Client()))
				);
				break;
			case Channels::Channel::ChannelType::GroupDirectMessage:
				m_channels.Add
				(
					Client().Channels().Add(Channels::GroupDirectMessage(channel, Client()))
				);
				break;
			case Channels::Channel::ChannelType::GuildCategory:
				m_channels.Add
				(
					Client().Channels().Add(Channels::GuildCategory(channel, Client()))
				);
				break;
			case Channels::Channel::ChannelType::GuildNews:
				m_channels.Add
				(
					Client().Channels().Add(Channels::GuildNews(channel, Client()).As<Channels::Channel>())
				);
				break;
			case Channels::Channel::ChannelType::GuildStore:
				m_channels.Add
				(
					Client().Channels().Add(Channels::GuildStore(channel, Client()))
				);
				break;
			case Channels::Channel::ChannelType::GuildText:
				m_channels.Add
				(
					Client().Channels().Add(Channels::GuildText(channel, Client()).As<Channels::Channel>())
				);
				break;
			default:
				m_channels.Add
				(
					Client().Channels().Add(Channels::Channel(channel, Client()))
				);
				break;
			}
		}
	}
}