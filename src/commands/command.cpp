#include "commands/command.hpp"

#include "structures/message.hpp"

namespace Ethyme::Commands
{
	Command::Command()
	{}

	Command::Command(const Command& command)
		: m_callback{ command.Callback() }
	{
		for (auto& arg : command.Arguments())
			m_arguments[arg.first] = { arg.second };
	}

	Command::Command(std::function<void(const Structures::Message&, std::unordered_map<std::string, Argument> arguments)> callback, const std::initializer_list<std::pair<std::string, Argument::ArgumentType>>& arguments)
		: m_callback(callback)
	{
		for (auto& arg : arguments)
			m_arguments[arg.first] = { arg.second };
	}

	Command& Command::SetArgument(const std::string& name, const Argument& argument)
	{
		m_arguments[name] = argument;
		return *this;
	}

	const std::unordered_map<std::string, Commands::Command::Argument>& Command::Arguments() const
	{
		return m_arguments;
	}
	
	std::function<void(const Structures::Message&, std::unordered_map<std::string, Command::Argument>)> Command::Callback() const
	{
		return m_callback;
	}

	void Command::Execute(const Structures::Message& message, std::unordered_map<std::string, Argument> arguments)
	{
		m_callback(message, arguments);
	}
}