#include "structures/channels/guildnews.hpp"

#include "client.hpp"

namespace Ethyme::Structures::Channels
{
	GuildNews::GuildNews(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client)
		: GuildText{ data, client }
		, Channel{ data, client }
	{}
}