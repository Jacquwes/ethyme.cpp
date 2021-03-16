#pragma once

#include "common.hpp"
#include "structures/channels/guildchannel.hpp"

namespace Ethyme
{
	class Client;

	namespace Structures::Channels
	{
		class GuildCategory : public GuildChannel
		{
		public:
			GuildCategory(nlohmann::json const& data, Ethyme::Client& client);
		};
	} // namespace Structures::Channels
} // namespace Strucutres::Ethyme