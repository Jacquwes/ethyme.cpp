#pragma once

#include "../common.hpp"
#include "event.hpp"

namespace Ethyme
{
	class Client;
}

namespace Ethyme::Events
{
	/**
	 * @brief Event triggered when the Client is ready to receive other events.
	*/
	class Ready : public Event
	{
	public:
		/**
		 * @brief Event's constructor
		 * @param client Ready Client's instance
		*/
		Ready(Ethyme::Client const& client);

		/**
		 * @brief Client
		 * @return Ready Client's instance
		*/
		Ethyme::Client const& Client() const;

	private:
		Ethyme::Client const& m_client;
	};
}