#include "structures/mentions.hpp"

#include "client.hpp"

namespace Ethyme::Structures
{
	Mentions::Mentions(
		Collections::Collection<Channels::Channel, true> const& channels,
		Collections::Collection<User, true> const& users
	)
		: m_channels{ channels }
		, m_users{ users }
	{}

	Collections::Collection<Channels::Channel, true> const& Mentions::Channels() const { return m_channels; }
	Collections::Collection<User, true> const& Mentions::Users() const { return m_users; }
}