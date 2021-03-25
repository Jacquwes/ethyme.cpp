#include "structures/channels/guildvoice.hpp"

#include "client.hpp"

namespace Ethyme::Structures::Channels
{
    GuildVoice::GuildVoice(nlohmann::json const& data, Ethyme::Client& client)
        : GuildChannel{ data, client }
    {}
}