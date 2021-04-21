#include "structures/channels/guildtext.hpp"

#include "client.hpp"

namespace Ethyme::Structures::Channels
{
	GuildText::GuildText(nlohmann::json const& data, Ethyme::Client& client)
		: GuildChannel{ data, client }
		, TextChannel{ data, client }
		, m_parent{
			data.contains("parent_id") && !data["parent_id"].is_null()
			? this->Guild().Channels().Find(
				[&](Channel& c)
				{
					return data["parent_id"] == c.Id();
				})->As<GuildCategory>()
			: const_cast<Channels::Channel&>(this->As<Channel>().Client().UnknownChannel()).As<GuildCategory>()
		}
		, m_nsfw{ data.contains("nsfw") ? data["nsfw"].get<bool>() : false }
		, m_topic{ data.contains("topic") && !data["topic"].is_null() ? data["topic"] : "" }
	{}

	GuildCategory& GuildText::Parent() { return m_parent; }
	bool const& GuildText::Nsfw() const { return m_nsfw; }
	std::string const& GuildText::Topic() const { return m_topic; }
}