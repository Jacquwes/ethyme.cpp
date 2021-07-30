#pragma once

#include "common.hpp"
#include "structures/channels/guildchannel.hpp"

namespace Ethyme
{
	class Client;

	namespace Structures::Channels
	{
		class GuildStore : public GuildChannel
		{
		public:
			GuildStore(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client);
		};
	}
}