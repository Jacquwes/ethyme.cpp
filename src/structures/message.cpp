#include "structures/message.hpp"

#include "client.hpp"
#include "structures/channels/textchannel.hpp"
#include "structures/user.hpp"

namespace Ethyme::Structures
{
	Message::Message(nlohmann::json const& data, Ethyme::Client const& client)
		: m_content(data["content"].get<std::string>())
		, Entity(data["id"].get<std::string>(), client)
		, m_author(User(data["author"], client))
		, m_channel(client.Channels().FindById(data["channel_id"]).As<TextChannel>())
		// , m_mentions(m_channelsMentions, m_usersMentions)
	{
		/*
		for (auto const& channelMention : data["mentions_channels"])
			// very very bad code sry guys imma fix it later
			m_channelsMentions.Add(std::make_shared<Structures::Channel>(client.Channels().FindById(channelMention["id"].get<std::string>())));
		for (auto const& userMention : data["mentions"])
			m_usersMentions.Add()
		*/
	}

	Structures::User const& Message::Author() const { return m_author; }
	Structures::TextChannel const& Message::Channel() const { return m_channel; }
	std::string const& Message::Content() const { return m_content; }
	// Structures::Mentions const& Message::Mentions() const { return m_mentions; }
}