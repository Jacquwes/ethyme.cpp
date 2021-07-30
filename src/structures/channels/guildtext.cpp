#include "structures/channels/guildtext.hpp"

#include "client.hpp"

namespace Ethyme::Structures::Channels
{
	GuildText::GuildText(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client)
		: GuildChannel{ data, client }
		, Channel{ data, client }
		, TextChannel{ data, client }
		, m_parent{
			data.contains("parent_id") && !data["parent_id"].is_null()
			? std::dynamic_pointer_cast<GuildCategory>(Guild()->Channels().Find(
				[&](std::shared_ptr<Channel>& c)
				{
					return data["parent_id"] == c->Id();
				}).get())
			: std::dynamic_pointer_cast<GuildCategory>(TextChannel::Client()->UnknownChannel())
		}
		, m_nsfw{ data.contains("nsfw") ? data["nsfw"].get<bool>() : false }
		, m_topic{ data.contains("topic") && !data["topic"].is_null() ? data["topic"] : "" }
	{}

	std::shared_ptr<GuildCategory>& GuildText::Parent() { return m_parent; }
	bool const& GuildText::Nsfw() const { return m_nsfw; }
	std::string const& GuildText::Topic() const { return m_topic; }
}