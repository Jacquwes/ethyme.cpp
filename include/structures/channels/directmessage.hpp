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
			DirectMessage(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client);

			std::shared_ptr<User>& Recipient();

		private:
			std::shared_ptr<User>& m_recipient;
		};
	} // namespace Structures::Channels
} // namespace Ethyme