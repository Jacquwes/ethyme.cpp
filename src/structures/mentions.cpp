#include "structures/mentions.hpp"

#include "client.hpp"

namespace Ethyme::Structures
{
	Mentions::Mentions(
		Collections::Collection<std::shared_ptr<Channels::Channel>>& channels,
		Collections::Collection<std::shared_ptr<User>>& users
	)
		: m_channels{ channels }
		, m_users{ users }
	{}

	Collections::Collection<std::shared_ptr<Channels::Channel>>& Mentions::Channels() { return m_channels; }
	Collections::Collection<std::shared_ptr<User>>& Mentions::Users() { return m_users; }
}