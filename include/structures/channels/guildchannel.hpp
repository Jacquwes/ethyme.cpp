#pragma once

#include "common.hpp"
#include "structures/channels/channel.hpp"

namespace Ethyme
{
	class Client;

	namespace Structures
	{
		class Guild;

		namespace Channels
		{
			class GuildChannel : public Channel
			{
			public:
				GuildChannel(ChannelType const& channelType, nlohmann::json const& data, Ethyme::Client& client);

				Structures::Guild& Guild();
				std::string const& Name() const;

			private:
				Structures::Guild& m_guild;
				std::string m_name;
			};
		} // namespace channels
	} // namespace Structures
} // namespace Ethyme
