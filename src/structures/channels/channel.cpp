#include "structures/channels/channel.hpp"

namespace Ethyme::Structures
{
	Channel::Channel(ChannelType const& channelType, std::string const& id, Ethyme::Client& client)
		: m_channelType(channelType)
		, Entity(id, client)
	{}

	const Channel::ChannelType& Channel::Type() const
	{
		return m_channelType;
	}
}