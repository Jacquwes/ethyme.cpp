#include "structures/channels/directmessage.hpp"

#include "client.hpp"

namespace Ethyme::Structures::Channels
{
	DirectMessage::DirectMessage(nlohmann::json const& data, Ethyme::Client& client)
		: TextChannel{ data, client }
		, m_recipient{ *client.Users().FindById(data["recipients"][0]["id"].get<std::string>()) }
	{}
	
	User& DirectMessage::Recipient() { return m_recipient; }
}