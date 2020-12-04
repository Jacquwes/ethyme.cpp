#include "ethyme.hpp"

#include <iostream>

using namespace Ethyme;

int main()
{
	Ethyme::Client client("Bot token");
	client.SetPrefix("!");

	// Command example
	client.AddCommand("greet", Ethyme::Command(
		// callback
		[&](const Ethyme::Structures::Message& message, std::unordered_map<std::string, Ethyme::Command::Argument> arguments)
		{
			// If no default value
			// std::string name = "World";
			// if (arguments["name"].Value)
			std::string name = std::get<std::string>(*arguments["name"].Value);
			message.Channel().Send("Hello " + name + "!");

			// Triggered with "!greet"
			// or "!greet --name some name"
		},
		// arguments
		{
			{
				"name", // name
				{
					false, // required
					Ethyme::Command::ArgumentType::String, // type
					std::string("World") // default value, don't forget to cast
				}
			}
		}
	));

	// handler example
	client.AddHandler(
		Ethyme::EventType::MessageCreate,
		[&](const Ethyme::Events::Event& event)
		{
			// ugly cast
			auto messageEvent = *(Ethyme::Events::MessageCreate*)&event;
			auto message = messageEvent.Message();

			if (!message.Author().Bot()
				&& message.Content() == "!ping")
				message.Channel().Send("pong hahaha");
		},
		"handler ID" // optional, random if not specified.
	);

	try
	{
		client.Start();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}