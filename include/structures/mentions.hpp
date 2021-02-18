#pragma once

#include "common.hpp"
#include "channels/channel.hpp"
#include "collection.hpp"
#include "user.hpp"

namespace Ethyme::Structures
{
	class Message;

	class Mentions
	{
	public:
		Mentions(Collection<std::shared_ptr<Channel>> const& channels, Collection<std::shared_ptr<User>> const& users);

		Collection<std::shared_ptr<Channel>> const& Channels() const;
		Collection<std::shared_ptr<User>> const& Users() const;

	private:
		Collection<std::shared_ptr<Channel>> const& m_channels;
		Collection<std::shared_ptr<User>> const& m_users;
	};
}