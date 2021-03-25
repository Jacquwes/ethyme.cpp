#include "structures/channels/guildcategory.hpp"

#include "client.hpp"

namespace Ethyme::Structures::Channels
{
    GuildCategory::GuildCategory(nlohmann::json const& data, Ethyme::Client& client)
        : GuildChannel(data, client)
    {}
}