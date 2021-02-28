#pragma once

#include "common.hpp"
#include "events/event.hpp"
#include "structures/guild.hpp"

namespace Ethyme::Events
{
	class GuildCreate : public Event
	{
	public:
		GuildCreate(Structures::Guild& guild);

		Structures::Guild& Guild() const;

	private:
		Structures::Guild& m_guild;
	};

}