#pragma once

#include "common.hpp"

#include "channels/channel.hpp"

#include "collections/collection.hpp"

#include "user.hpp"

namespace Ethyme::Structures
{
	class Message;

	/**
	 * @brief Used by Message class to store all mentions in it.
	*/
	class Mentions
	{
	public:
		Mentions(Collections::Collection<std::shared_ptr<Channels::Channel>>& channels, Collections::Collection<std::shared_ptr<User>>& users);

		Collections::Collection<std::shared_ptr<Channels::Channel>>& Channels();
		Collections::Collection<std::shared_ptr<User>>& Users();

	private:
		Collections::Collection<std::shared_ptr<Channels::Channel>>& m_channels;
		Collections::Collection<std::shared_ptr<User>>& m_users;
	};
}