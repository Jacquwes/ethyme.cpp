#include "events/ready.hpp"

#include "client.hpp"

namespace Ethyme::Events
{
	Ready::Ready(std::shared_ptr<Ethyme::Client> client)
		: m_client{ client }
	{}

	std::shared_ptr<Ethyme::Client> Ready::Client() const { return m_client; }
}