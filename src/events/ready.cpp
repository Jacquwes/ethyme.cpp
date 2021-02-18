#include "events/ready.hpp"

#include "client.hpp"

namespace Ethyme::Events
{
	Ready::Ready(Ethyme::Client const& client)
		: m_client{ client }
	{}

	Ethyme::Client const& Ready::Client() const { return m_client; }
}