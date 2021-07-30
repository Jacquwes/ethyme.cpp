#pragma once

#include "common.hpp"
#include "structures/channels/guildchannel.hpp"

namespace Ethyme
{
	class Client;

	namespace Structures::Channels
	{
		class GuildVoice : public GuildChannel
		{
		public:
			GuildVoice(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client);
		};
	}
}