#include "events/guildcreate.hpp"

namespace Ethyme::Events
{
	GuildCreate::GuildCreate(Structures::Guild& guild)
		: m_guild{ guild }
	{}

	Structures::Guild& GuildCreate::Guild() const
	{
		return m_guild;
	}
}