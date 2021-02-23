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
		Mentions(Collections::Collection<std::reference_wrapper<Channel>> const& channels, Collections::Collection<std::reference_wrapper<User>> const& users);

		Collections::Collection<std::reference_wrapper<Channel>> const& Channels() const;
		Collections::Collection<std::reference_wrapper<User>> const& Users() const;

	private:
		Collections::Collection<std::reference_wrapper<Channel>> const& m_channels;
		Collections::Collection<std::reference_wrapper<User>> const& m_users;
	};
}