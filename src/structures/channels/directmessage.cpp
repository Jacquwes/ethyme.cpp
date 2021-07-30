#include "structures/channels/directmessage.hpp"

#include "client.hpp"

namespace Ethyme::Structures::Channels
{
	DirectMessage::DirectMessage(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client)
		: TextChannel{ data, client }
		, Channel{ data, client }
		, m_recipient{ client->Users().FindById(data["recipients"][0]["id"].get<std::string>()).get() }
	{}
	
	std::shared_ptr<User>& DirectMessage::Recipient() { return m_recipient; }
}