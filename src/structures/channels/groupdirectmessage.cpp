#include "structures/channels/groupdirectmessage.hpp"

#include "client.hpp"

namespace Ethyme::Structures::Channels
{
    GroupDirectMessage::GroupDirectMessage(nlohmann::json const& data, Ethyme::Client& client)
        : TextChannel(data, client)
        , m_recipients{ client, Constants::API::Users }
    {
        for (const auto& recipient : data["recipients"])
            m_recipients.Add(*client.Users().FindById(recipient["id"]));
    }

    Collections::Collection<User, true>& GroupDirectMessage::Recipients()
    {
        return m_recipients;
    }
}