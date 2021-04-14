#include "structures/channels/guildtext.hpp"

#include "client.hpp"

namespace Ethyme::Structures::Channels
{
    GuildText::GuildText(nlohmann::json const& data, Ethyme::Client& client)
        : GuildChannel{ data, client }
        , TextChannel{ data, client }
        , m_parent{ this->Guild().Channels().Find([&](auto c) { return data["parent_id"] == c.get().Id(); })->get().As<GuildCategory>() }
        , m_nsfw{ data["nsfw"] }
        , m_topic{ data.contains("topic") ? data["topic"] : "" }
    {}

    GuildCategory& GuildText::Parent() { return m_parent; }
    bool const& GuildText::Nsfw() const { return m_nsfw; }
    std::string const& GuildText::Topic() const { return m_topic; }
}