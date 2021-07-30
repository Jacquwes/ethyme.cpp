#include "structures/channels/guildvoice.hpp"

#include "client.hpp"

namespace Ethyme::Structures::Channels
{
    GuildVoice::GuildVoice(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client)
        : GuildChannel{ data, client }
        , Channel{ data, client }
    {}
}