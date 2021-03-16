#pragma once

#include "common.hpp"
#include "structures/channels/textchannel.hpp"
#include "structures/user.hpp"

namespace Ethyme
{
	class Client;

	namespace Structures::Channels
	{
		class DirectMessage : public TextChannel
		{
		public:
			DirectMessage(nlohmann::json const& data, Ethyme::Client& client);

			User& Recipient();

		private:
			User& m_recipient;
		};
	} // namespace Structures::Channels
} // namespace Ethyme