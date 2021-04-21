#include "structures/channels/channel.hpp"

namespace Ethyme::Structures::Channels
{
	Channel::Channel(nlohmann::json const& data, Ethyme::Client& client)
		: m_channelType(data.contains("type") ? data["type"].get<ChannelType>() : ChannelType::GuildText)
		, Entity(data.contains("id") ? data["id"].get<std::string>() : "000000000000000000", client, false, data)
	{}

	const Channel::ChannelType& Channel::Type() const
	{
		return m_channelType;
	}
}