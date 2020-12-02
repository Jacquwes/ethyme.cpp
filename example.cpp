#include "include/ethyme.hpp"

#include <iostream>

using namespace Ethyme;
using namespace Commands;

int main()
{
	Ethyme::Client client("Bot token");

	client.SetPrefix("!");
	client.AddCommand("test", Ethyme::Commands::Command(
		[&](const Ethyme::Structures::Message& message, std::unordered_map<std::string, Ethyme::Commands::Command::Argument> arguments)
		{
			std::string desc = "bot: " + std::string(std::holds_alternative<bool>(arguments["bot"].Value) ? std::get<bool>(arguments["bot"].Value) ? "true" : "false" : "false");
			desc += "\ndesc: " + std::get<std::string>(arguments["desc"].Value);
			message.Channel().Send(desc);
		},
		{
			{
				"bot",
				Command::Argument::ArgumentType::Bool,
			},
			{
				"desc",
				Command::Argument::ArgumentType::String,
			}
		}
	));

	try
	{
		client.Start();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}