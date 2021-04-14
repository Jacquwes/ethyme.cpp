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

			Collections::Collection<User, true>& Recipients();

		private:
			Collections::Collection<User, true> m_recipients;
		};
	} // namespace Structures::Channels
} // namespace Ethyme