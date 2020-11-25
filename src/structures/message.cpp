#include "structures/message.hpp"

namespace Ethyme::Structures
{
	Message::Message(const nlohmann::json& data)
		: m_author(nullptr)
		, m_content(data["content"])
		, Entity(data["id"])
	{}

	std::shared_ptr<const Structures::User> Message::Author() const { return m_author; }
	const std::string& Message::Content() const { return m_content; }

}