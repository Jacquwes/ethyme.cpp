#include "events/guildcreate.hpp"

namespace Ethyme::Events
{
	GuildCreate::GuildCreate(std::shared_ptr<Structures::Guild>& guild)
		: m_guild{ guild }
	{}

	std::shared_ptr<Structures::Guild>& GuildCreate::Guild() const
	{
		return m_guild;
	}
}