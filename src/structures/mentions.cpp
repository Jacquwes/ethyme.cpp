#include "structures/mentions.hpp"

#include "client.hpp"

namespace Ethyme::Structures
{
	Mentions::Mentions(
		Collections::Collection<std::reference_wrapper<Channels::Channel>> const& channels,
		Collections::Collection<std::reference_wrapper<User>> const& users
	)
		: m_channels{ channels }
		, m_users{ users }
	{}

	Collections::Collection<std::reference_wrapper<Channels::Channel>> const& Mentions::Channels() const { return m_channels; }
	Collections::Collection<std::reference_wrapper<User>> const& Mentions::Users() const { return m_users; }
}