#include "structures/channels/textchannel.hpp"

#include "client.hpp"
#include "constants.hpp"
#include "structures/message.hpp"

namespace Ethyme::Structures
{
	TextChannel::TextChannel(const nlohmann::json& data, const Ethyme::Client& client)
		: Channel(static_cast<Channel::ChannelType>(data["type"]), data["id"], client)
	{}

	cppcoro::task<Message> TextChannel::Send(const std::string& content) const
	{
		nlohmann::json body;
		body["content"] = content;

		auto response = cpr::Post(
			cpr::Url{ Constants::API::Channels + Id().ToString() + "/messages" },
			cpr::Header{
				{ "Authorization", this->Client().Token() },
				{ "Content-Type", "application/json" } 
			},
			cpr::Body{ body.dump() }
		);

		Logger::Debug("Message sent to " + Id().ToString());

		co_return Message(nlohmann::json::parse(response.text), Client());
	}
}