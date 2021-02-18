#include "structures/mentions.hpp"

#include "client.hpp"

namespace Ethyme::Structures
{
	Mentions::Mentions(
		Collection<std::shared_ptr<Channel>> const& channels, 
		Collection<std::shared_ptr<User>> const& users
	)
		: m_channels{ channels }
		, m_users{ users }
	{}

	Collection<std::shared_ptr<Channel>> const& Mentions::Channels() const { return m_channels; }
	Collection<std::shared_ptr<User>> const& Mentions::Users() const { return m_users; }
}