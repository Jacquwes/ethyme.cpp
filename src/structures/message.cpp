#include "structures/message.hpp"

#include "client.hpp"
#include "structures/channels/textchannel.hpp"
#include "structures/user.hpp"

namespace Ethyme::Structures
{
	Message::Message(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client)
		: m_content{ data["content"].get<std::string>() }
		, Entity{ data["id"].get<std::string>(), client, false, data }
		, m_author{ std::make_shared<User>(data["author"], client) }
		, m_channel{ std::dynamic_pointer_cast<Channels::TextChannel>(*(client->Channels().FindById(data["channel_id"].get<std::string>()))) }
	{}

	std::shared_ptr<Structures::User> Message::Author() { return m_author; }
	std::shared_ptr<Structures::Channels::TextChannel> Message::Channel() { return m_channel; }
	std::string const& Message::Content() const { return m_content; }

	cppcoro::task<std::shared_ptr<Message>> Message::Delete()
	{
		cpr::Delete(
			cpr::Url{ Constants::API::Channels + Channel()->Id().ToString() + "/messages/" + Id().ToString() },
			cpr::Header{
				{ "Authorization", this->Client()->Token() },
				{ "Content-Type", "application/json" }
			}
		);

		Logger::Debug("Message deleted in channel " + Channel()->Id().ToString());

		co_return this->shared_from_this();
	}
	// Structures::Mentions const& Message::Mentions() const { return m_mentions; }
}