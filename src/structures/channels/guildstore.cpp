#include "structures/channels/guildstore.hpp"

#include "client.hpp"

namespace Ethyme::Structures::Channels
{
    GuildStore::GuildStore(nlohmann::json const& data, Ethyme::Client& client)
        : GuildChannel{ data, client }
    {}
}