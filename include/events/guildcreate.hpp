#pragma once

#include "common.hpp"
#include "events/event.hpp"
#include "structures/guild.hpp"

namespace Ethyme::Events
{
	class GuildCreate : public Event
	{
	public:
		GuildCreate(std::shared_ptr<Structures::Guild>& guild);

		std::shared_ptr<Structures::Guild>& Guild() const;

	private:
		std::shared_ptr<Structures::Guild>& m_guild;
	};

}