#include "ethyme.hpp"

#include <iostream>

#include "commands/channel.hpp"
#include "commands/greet.hpp"
#include "commands/guilds.hpp"

int main()
{
	Ethyme::Logger::SetLogLevel(
		(int)Logger::Level::Debug
		| (int)Logger::Level::Infos
		| (int)Logger::Level::Errors
	);

	try
	{
		Ethyme::Client client("Bot Token");
		client.SetPrefix("!");

		// Command example
		client.AddCommand("channel", ChannelCommand);
		client.AddCommand("greet", GreetCommand);
		client.AddCommand("guilds", GuildsCommand);

		// handler example
		client.AddHandler(
			Ethyme::EventType::MessageCreate,
			[&](Ethyme::Events::Event& event) -> cppcoro::task<>
			{
				auto messageEvent = event.As<Ethyme::Events::MessageCreate>();
				auto message = messageEvent.Message();

				if (!message->Author()->Bot()
					&& message->Content() == "!ping")
					co_await message->Channel()->Send("pong hahaha");
			},
			"handler ID" // optional, random if not specified.
				);

		client.AddHandler(
			Ethyme::EventType::Ready,
			[&](Ethyme::Events::Event& event) -> cppcoro::task<>
			{
				auto readyEvent = event.As<Ethyme::Events::Ready>();
				Logger::Info(std::string(*readyEvent.Client()->User()) + " is online!");
				co_return;
			}
		);

		client.Start();
	}
	catch (Ethyme::Exception e)
	{
		Ethyme::Logger::Error(e.what());
	}
}