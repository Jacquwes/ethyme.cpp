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
		Ready(std::shared_ptr<Ethyme::Client> client);

		/**
		 * @brief Client
		 * @return Ready Client's instance
		*/
		std::shared_ptr<Ethyme::Client> Client() const;

	private:
		std::shared_ptr<Ethyme::Client> m_client;
	};
}