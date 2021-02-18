#pragma once

#include "../common.hpp"
#include "event.hpp"

namespace Ethyme
{
	class Client;
}

namespace Ethyme::Events
{
	class Ready : public Event
	{
	public:
		Ready(Ethyme::Client const& client);

		Ethyme::Client const& Client() const;

	private:
		Ethyme::Client const& m_client;
	};
}