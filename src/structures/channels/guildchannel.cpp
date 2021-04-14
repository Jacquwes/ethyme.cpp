#include "structures/channels/guildchannel.hpp"

#include "client.hpp"
#include "structures/guild.hpp"

namespace Ethyme::Structures::Channels
{
	GuildChannel::GuildChannel(nlohmann::json const& data, Ethyme::Client& client)
		: Channel	{ data, client }
		, m_guild	{ *client.Guilds().FindById(data["guild_id"].get<std::string>()) }
		, m_name	{ data["name"].get<std::string>() }
		, m_position{ data["position"].get<uint16_t>() }
	{}

	Structures::Guild& GuildChannel::Guild() { return m_guild; }
	std::string const& GuildChannel::Name() const { return m_name; }
	uint16_t const& GuildChannel::Position() const { return m_position; }
}