#include "client.hpp"
#include "constants.hpp"
#include "structures/channel.hpp"
#include "structures/message.hpp"

namespace Ethyme::Structures
{
	Channel::Channel(const ChannelType& channelType, const std::string& id, const std::shared_ptr<Ethyme::Client>& client)
		: m_type(channelType)
		, Entity(id, client)
	{}

	const Channel::ChannelType& Channel::Type() const
	{
		return m_type;
	}

	TextChannel::TextChannel(const nlohmann::json& data, const std::shared_ptr<Ethyme::Client>& client)
		: Channel(static_cast<ChannelType>(data["type"]), data["id"], client)
	{}

	void TextChannel::Send(const std::string& content) const
	{
		//return std::async([&]() -> std::shared_ptr<const Message>
			{
				nlohmann::json data;
				data["content"] = content;

				auto response = cpr::Post(
					cpr::Url(Constants::API::Channels + Id().ToString() + "/messages"),
					cpr::Header{ {"Authorization", Client()->Token() } },
					cpr::Header{ {"Content-Type", "application/json"} },
					cpr::Body{ data.dump() }
				);

				//return std::shared_ptr<const Message>(new Message(nlohmann::json::parse(response.text), Client()));
			}//);
	}
}