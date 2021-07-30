#pragma once

#include "common.hpp"
#include "structures/channels/guildtext.hpp"

namespace Ethyme
{
	class Client;

	namespace Structures::Channels
	{
		class GuildNews : public GuildText
		{
		public:
			GuildNews(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client);
		};
	}
}