#include "structures/channels/groupdirectmessage.hpp"

#include "client.hpp"

namespace Ethyme::Structures::Channels
{
    GroupDirectMessage::GroupDirectMessage(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client)
        : TextChannel{ data, client }
        , Channel{ data, client }
        , m_recipients{ client, Constants::API::Users }
    {
        for (const auto& recipient : data["recipients"])
            m_recipients.Add(client->Users().FindById(recipient["id"]).get());
    }

    Collections::Collection<std::shared_ptr<User>> const& GroupDirectMessage::Recipients() const
    {
        return m_recipients;
    }
}