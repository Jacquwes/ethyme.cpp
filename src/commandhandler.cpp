#include "client.hpp"

#include "structures/channels/textchannel.hpp"

namespace Ethyme
{
	void Client::SetupCommandHandler()
	{
		AddHandler(
			EventType::MessageCreate,
			[&](const Events::Event& event)
			{
				auto& message = (*(Events::MessageCreate*)&event).Message();
				auto& content = message.Content();
				std::vector<std::string> arguments = { "" };

				// check prefix
				if (content.rfind(m_prefix, 0)) return;

				// parse arguments
				for (auto& i : content)
					if (i == ' ' || i == '\n' || i == '\r')
					{
						if (!arguments.back().empty())
							arguments.push_back("");
					}
					else
						arguments.back().push_back(i);

				// check arguments number
				if (!arguments.size()) return;

				// find command
				std::string commandName = arguments[0].substr(m_prefix.size());
				arguments.erase(arguments.begin());
				auto baseCommand = std::find_if(m_commands.begin(), m_commands.end(),
					[&](const std::pair<std::string, Command>& command_)
					{
						return commandName == command_.first;
					});
				if (baseCommand == m_commands.end()) return;

				// create copy of command
				std::pair<std::string, Command> command = *baseCommand;
				// find command arguments
				std::pair<std::string, Command::Argument*> currentArgument{ "", nullptr };
				if (baseCommand->second.Arguments().size())
				{
					currentArgument = { command.second.Arguments().begin()->first, &command.second.Arguments().begin()->second };
				}

				std::vector<std::string> errors;
				int i = 0;
				for (auto& argument : arguments)
				{
					if (!argument.rfind("--", 0))
					{
						if (!command.second.Arguments().count(argument.substr(2)))
							errors.push_back("Argument `" + argument.substr(2) + "` unknown.");
						else
						{
							currentArgument = { argument.substr(2), &command.second.Arguments()[argument.substr(2)] };
							currentArgument.second->Value = std::nullopt;
						}
					}
					else if (currentArgument.second)
					{
						using t = Command::ArgumentType;
						switch (currentArgument.second->Type)
						{
						case t::Bool:
						{
							if (currentArgument.second->Value.has_value())
							{
								errors.push_back("Redefinition of boolean argument `" + currentArgument.first + "`.");
								break;
							}
							std::transform(argument.begin(), argument.end(), argument.begin(), [&](auto c) { return std::tolower(c); });
							if (
								argument == "n" ||
								argument == "no" ||
								argument == "false" ||
								argument == "f"
								)
								currentArgument.second->Value = false;
							else if (
								argument == "y" ||
								argument == "yes" ||
								argument == "true" ||
								argument == "t"
								)
								currentArgument.second->Value = true;
							else
								errors.push_back("`" + argument + "` is not a valid boolean argument.");
							break;
						}
						case t::String:
						{
							if(!i)
								currentArgument.second->Value = std::nullopt;
							if (currentArgument.second->Value)
								std::get<std::string>(*currentArgument.second->Value) += " " + argument;
							else
								currentArgument.second->Value = argument;
							break;
						}
						case t::Int:
						{
							if (currentArgument.second->Value.has_value())
							{
								errors.push_back("Redefinition of number argument `" + currentArgument.first + "`.");
								break;
							}
							try
							{
								currentArgument.second->Value = std::stoi(argument);
							}
							catch (const std::exception&)
							{
								errors.push_back("`" + argument + "` is not a valid number argument.");
								currentArgument.second->Value == std::nullopt;
							}
							break;
						}
						case t::Double:
						{
							if (currentArgument.second->Value.has_value())
							{
								errors.push_back("Redefinition of number argument `" + currentArgument.first + "`.");
								break;
							}
							try
							{
								currentArgument.second->Value = std::stod(argument);
							}
							catch (const std::exception&)
							{
								errors.push_back("`" + argument + "` is not a valid number argument.");
								currentArgument.second->Value == std::nullopt;
							}
							break;
						}
						default:
							break;
						}
					}
					++i;
				}

				for (auto& arg : command.second.Arguments())
					if (!arg.second.Value && arg.second.Required)
						errors.push_back("Required argument `" + arg.first + "` not found.");

				if (!errors.empty())
				{
					std::string errorMessage = "<@" + message.Author().Id().ToString() + ">, your command couldn't be processed:\n";
					for (auto& error : errors)
						errorMessage += error + "\n";
					message.Channel().Send(errorMessage);
					return;
				}

				command.second.Callback()(message, command.second.Arguments());
			},
			"commandHandler"
		);
	}
}