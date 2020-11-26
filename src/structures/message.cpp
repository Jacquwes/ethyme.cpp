#include "structures/message.hpp"

#include "structures/channel.hpp"

namespace Ethyme::Structures
{
	Message::Message(const nlohmann::json& data, const std::shared_ptr<Ethyme::Client>& client)
		: m_content(data["content"])
		, Entity(data["id"], client)
		, m_author(std::shared_ptr<Structures::User>(new User(data["user"], client)))
	{}

	const std::shared_ptr<Structures::User>& Message::Author() const { return m_author; }
	const std::shared_ptr<const Structures::TextChannel>& Message::Channel() const { return m_channel; }
	const std::string& Message::Content() const { return m_content; }

}