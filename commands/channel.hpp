#include "ethyme.hpp"

using namespace Ethyme;

inline auto ChannelCommand = Command(
	[&](Structures::Message& message, std::unordered_map<std::string, Command::Argument> arguments) -> cppcoro::task<>
	{
		std::stringstream text;
		auto& m = message;
		auto guildChannel = *(Structures::Channels::GuildChannel*)&message.Channel();
		auto channel = *(Structures::Channels::GuildText*)&guildChannel;
		
		// I'm so sorry for that

		text
			<< "Guild: " << channel.Guild().Name() << " (" << channel.Guild().Id() << ")\n"
			<< "Name: " << channel.Name() << "\n"
			<< "Nsfw: " << (channel.Nsfw() ? "yes" : "no") << "\n"
			<< "Parent: " << channel.Parent().Name() << " (" << channel.Parent().Id() << ")\n"
			<< "Topic: " << channel.Topic() << "\nwow so much members right?";

		message.Channel().Send(text.str());
		message.Channel().Send("https://cdn.discordapp.com/emojis/742399707418067044.png?v=1");

		co_return;
	}, {}
	);