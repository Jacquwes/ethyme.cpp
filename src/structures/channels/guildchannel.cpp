#include "structures/channels/guildchannel.hpp"

#include "client.hpp"
#include "structures/guild.hpp"

namespace Ethyme::Structures::Channels
{
	GuildChannel::GuildChannel(nlohmann::json const& data, Ethyme::Client& client)
		: Channel	{ data["id"].get<std::string>(), client }
		, m_guild	{ *client.Guilds().FindById(data["guild_id"].get<std::string>()) }
		, m_name	{ data["name"].get<std::string>() }
	{}

	Structures::Guild& GuildChannel::Guild() { return m_guild; }
	std::string const& GuildChannel::Name() const { return m_name; }
}