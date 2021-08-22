#include "structures/channels/guildchannel.hpp"

#include "client.hpp"
#include "structures/guild.hpp"

namespace Ethyme::Structures::Channels
{
	GuildChannel::GuildChannel(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client)
		: Channel	{ data, client }
		, m_guild	{ client->Guilds().FindById(data["guild_id"].get<std::string>()).get() }
		, m_name	{ data["name"].get<std::string>() }
		, m_position{ data["position"].get<uint16_t>() }
	{}

	cppcoro::task<> GuildChannel::Delete()
	{
		cpr::Delete(
			cpr::Url{ Constants::API::Channels + Id().ToString() },
			cpr::Header{
				{ "Authorization", Client()->Token() },
				{ "Content-Type", "application/json" }
			}
		);

		Client()->Channels().RemoveById(Id());

		co_return;
	}

	std::shared_ptr<Structures::Guild>& GuildChannel::Guild() { return m_guild; }
	std::string const& GuildChannel::Name() const { return m_name; }
	uint16_t const& GuildChannel::Position() const { return m_position; }
}