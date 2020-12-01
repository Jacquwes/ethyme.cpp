#include "structures/message.hpp"

#include "client.hpp"
#include "structures/channels/textchannel.hpp"
#include "structures/user.hpp"

namespace Ethyme::Structures
{
	Message::Message(const nlohmann::json& data, const Ethyme::Client& client)
		: m_content(data["content"].get<std::string>())
		, Entity(data["id"].get<std::string>(), client)
		, m_author(User(data["author"], client))
		, m_channel(client.Channels().FindById(data["channel_id"]).As<TextChannel>())
	{}

	const Structures::User& Message::Author() const { return m_author; }
	const Structures::TextChannel& Message::Channel() const { return m_channel; }
	const std::string& Message::Content() const { return m_content; }
}