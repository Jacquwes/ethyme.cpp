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
		Mentions(Collections::Collection<Channels::Channel, true> const& channels, Collections::Collection<User, true> const& users);

		Collections::Collection<Channels::Channel, true> const& Channels() const;
		Collections::Collection<User, true> const& Users() const;

	private:
		Collections::Collection<Channels::Channel, true> const& m_channels;
		Collections::Collection<User, true> const& m_users;
	};
}