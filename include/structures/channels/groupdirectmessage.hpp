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

			Collections::Collection<std::reference_wrapper<User>>& Recipients();

		private:
			Collections::Collection<std::reference_wrapper<User>> m_recipients;
		};
	} // namespace Structures::Channels
} // namespace Ethyme