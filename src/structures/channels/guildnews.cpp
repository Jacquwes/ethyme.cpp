#include "structures/channels/guildnews.hpp"

#include "client.hpp"

namespace Ethyme::Structures::Channels
{
    GuildNews::GuildNews(nlohmann::json const& data, Ethyme::Client& client)
        : GuildText{ data, client }
    {}
}