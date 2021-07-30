#pragma once

#include "common.hpp"

#include "structures/channels/guildcategory.hpp"
#include "structures/channels/textchannel.hpp"

namespace Ethyme
{
	class Client;

	namespace Structures::Channels
	{
		class GuildText : public GuildChannel, public TextChannel
		{
		public:
			GuildText(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client);

			std::shared_ptr<GuildCategory>& Parent();
			bool const& Nsfw() const;
			std::string const& Topic() const;

			template <typename T> inline T& As() { return Entity::As<T>(); }

		private:
			std::shared_ptr<GuildCategory> m_parent;
			bool m_nsfw;
			std::string m_topic;
		};
	}
}