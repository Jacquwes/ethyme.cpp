#include "commands/command.hpp"

#include "structures/message.hpp"

namespace Ethyme
{
	Command::Command(const std::function<cppcoro::task<>(Structures::Message& message, std::unordered_map<std::string, Argument> arguments)>& callback, std::unordered_map<std::string, Command::Argument> args)
		: arguments{ args }
	{
		m_callback = callback;
	}

	const std::function<cppcoro::task<>(Structures::Message& message, std::unordered_map<std::string, Command::Argument> arguments)>& Command::Callback() const
	{
		return m_callback;
	}

	std::unordered_map<std::string, Command::Argument>& Command::Arguments()
	{
		return arguments;
	}

	void Command::SetArgument(const std::string& name, std::optional<std::variant<bool, std::string, int, double>> value)
	{
		auto argument = arguments.find(name);
		if (argument == arguments.end()) return;
		argument->second.Value = value;
	}
}