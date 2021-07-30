#include "structures/channels/textchannel.hpp"

#include "client.hpp"
#include "constants.hpp"
#include "structures/message.hpp"

namespace Ethyme::Structures::Channels
{
	TextChannel::TextChannel(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client)
		: Channel(data, client)
	{}

	cppcoro::task<std::shared_ptr<Message>> TextChannel::Send(std::string const& content) const
	{
		nlohmann::json body;
		body["content"] = content;

		auto response = cpr::Post(
			cpr::Url{ Constants::API::Channels + Id().ToString() + "/messages" },
			cpr::Header{
				{ "Authorization", Client()->Token() },
				{ "Content-Type", "application/json" } 
			},
			cpr::Body{ body.dump() }
		);

		Logger::Debug("Message sent to " + Id().ToString());

		co_return std::make_shared<Message>(nlohmann::json::parse(response.text), this->Client());
	}
}