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
			GroupDirectMessage(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client);

			Collections::Collection<std::shared_ptr<User>> const& Recipients() const;

		private:
			Collections::Collection<std::shared_ptr<User>> m_recipients;
		};
	} // namespace Structures::Channels
} // namespace Ethyme