#include "ethyme.hpp"

using namespace Ethyme;

inline auto GreetCommand = 
	Command(
	// callback
	[&](Structures::Message& message, std::unordered_map<std::string, Command::Argument> arguments) -> cppcoro::task<>
	{
		// If no default value
		// std::string name = "World";
		// if (arguments["name"].Value)
		std::string name = std::get<std::string>(*arguments["name"].Value);
		std::string secondName = std::get<std::string>(*arguments["secondName"].Value);
		co_await message.Delete();

		auto sentMessage = co_await message.Channel().Send("Hello " + name + " and " + secondName + "!");
		Logger::Info(sentMessage.Content() + " sent in channel " + sentMessage.Channel().Id().ToString());

		// You have to use at least once "co_await <expression>" or "co_return;"
		// in a handler.

		// Triggered with "!greet"
		// or "!greet some name --secondName hahaha"
		// or "!greet --name some name --secondName hahaha"
	},
	// arguments
	{
		{
			"name", // name
			{
				false, // required
				Command::ArgumentType::String, // type
				std::string("World") // default value, don't forget to cast
			}
		},
		{
			"secondName",
			{
				false,
				Command::ArgumentType::String,
				std::string("Samuel")
			}
		}
	});
