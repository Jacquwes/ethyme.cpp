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
			class GuildChannel : public virtual Channel
			{
			public:
				GuildChannel(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client);

				std::shared_ptr<Structures::Guild>& Guild();
				std::string const& Name() const;
				uint16_t const& Position() const;

			private:
				std::shared_ptr<Structures::Guild>& m_guild;
				std::string m_name;
				uint16_t m_position;
			};
		} // namespace channels
	} // namespace Structures
} // namespace Ethyme
