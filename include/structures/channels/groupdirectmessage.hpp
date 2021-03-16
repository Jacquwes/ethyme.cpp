#pragma once

#include "common.hpp"
#include "collections/collection.hpp"
#include "structures/channels/textchannel.hpp"
#include "structures/user.hpp"

namespace Ethyme
{
	class Client;

	namespace Structures::Channels
	{
		class GroupDirectMessage : public TextChannel
		{
		public:
			GroupDirectMessage(nlohmann::json const& data, Ethyme::Client& client);

			Collections::Collection<std::reference_wrapper<User>>& Recipient();

		private:
			Collections::Collection<std::reference_wrapper<User>> m_recipient;
		};
	} // namespace Structures::Channels
} // namespace Ethyme