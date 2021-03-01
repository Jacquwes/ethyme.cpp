#include "structures/channels/channel.hpp"

namespace Ethyme::Structures::Channels
{
	Channel::Channel(nlohmann::json const& data, Ethyme::Client& client)
		: m_channelType(data["type"].get<ChannelType>())
		, Entity(data["id"].get<std::string>(), client)
	{}

	const Channel::ChannelType& Channel::Type() const
	{
		return m_channelType;
	}
}