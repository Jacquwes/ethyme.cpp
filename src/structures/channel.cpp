#include "structures/channel.hpp"

namespace Ethyme::Structures
{
	Channel::Channel(const ChannelType& channelType, const std::string& id, const Ethyme::Client& client)
		: m_channelType(channelType)
		, Entity(id, client)
	{}

	const Channel::ChannelType& Channel::Type() const
	{
		return m_channelType;
	}
}