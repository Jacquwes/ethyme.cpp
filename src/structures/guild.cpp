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
	Guild::Guild(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client, bool const& parse)
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

	Collections::Collection<std::shared_ptr<Channels::Channel>>& Guild::Channels() { return m_channels; }
	Collections::Collection<std::shared_ptr<Member>>& Guild::Members() { return m_members; }
	std::string const& Guild::Name() const { return m_name; }
	std::shared_ptr<Member>& Guild::Owner() { return *m_members.FindById(m_ownerId); }
	Collections::Collection<std::shared_ptr<Role>>& Guild::Roles() { return m_roles; }

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
		{
			auto role_ = std::make_shared<Role>(role, Client());
			m_roles.Add(role_);
		}
		for (auto& channel : channels)
		{
			if (!channel.contains("guild_id"))
				const_cast<nlohmann::json&>(channel)["guild_id"] = Data()[0]["id"].get<std::string>();
			switch (channel["type"].get<Channels::Channel::ChannelType>())
			{
			case Channels::Channel::ChannelType::DirectMessage:
			{
				auto channel_ = std::dynamic_pointer_cast<Channels::Channel>(std::make_shared<Channels::DirectMessage>(channel, Client()));
				m_channels.Add(Client()->Channels().Add(channel_));
				break;
			}
			case Channels::Channel::ChannelType::GroupDirectMessage:
			{
				auto channel_ = std::dynamic_pointer_cast<Channels::Channel>(std::make_shared<Channels::GroupDirectMessage>(channel, Client()));
				m_channels.Add(Client()->Channels().Add(channel_));
				break;
			}
			case Channels::Channel::ChannelType::GuildCategory:
			{
				auto channel_ = std::dynamic_pointer_cast<Channels::Channel>(std::make_shared<Channels::GuildCategory>(channel, Client()));
				m_channels.Add(Client()->Channels().Add(channel_));
				break;
			}
			case Channels::Channel::ChannelType::GuildNews:
			{
				auto channel_ = std::dynamic_pointer_cast<Channels::Channel>(std::make_shared<Channels::GuildNews>(channel, Client()));
				m_channels.Add(Client()->Channels().Add(channel_));
				break;
			}
			case Channels::Channel::ChannelType::GuildStore:
			{
				auto channel_ = std::dynamic_pointer_cast<Channels::Channel>(std::make_shared<Channels::GuildStore>(channel, Client()));
				m_channels.Add(Client()->Channels().Add(channel_));
				break;
			}
			case Channels::Channel::ChannelType::GuildText:
			{
				auto channel_ = std::dynamic_pointer_cast<Channels::Channel>(std::make_shared<Channels::GuildText>(channel, Client()));
				m_channels.Add(Client()->Channels().Add(channel_));
				break;
			}
			default:
			{
				auto channel_ = std::make_shared<Channels::Channel>(channel, Client());
				m_channels.Add(Client()->Channels().Add(channel_));
				break;
			}
			}
		}
	}
}