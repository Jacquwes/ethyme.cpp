#pragma once

#include "common.hpp"

namespace Ethyme::Structures
{
	class Message;
}

namespace Ethyme::Commands
{
	class Command
	{
	public:
		struct Argument
		{
			enum class ArgumentType
			{
				String,
				Int,
				Double,
				Bool,
			} Type;

			std::variant<std::string, int, double, bool> Value;
		};

		Command();
		Command(const Command& command);
		Command(std::function<void(const Structures::Message&, std::unordered_map<std::string, Argument>)> callback, const std::initializer_list<std::pair<std::string, Argument::ArgumentType>>& arguments = {});

		Command& SetArgument(const std::string& name, const Argument& argument);
		const std::unordered_map<std::string, Commands::Command::Argument>& Arguments() const;

		std::function<void(const Structures::Message&, std::unordered_map<std::string, Argument>)> Callback() const;
		void Execute(const Structures::Message& message, std::unordered_map<std::string, Argument> arguments);

	private:
		std::unordered_map<std::string, Commands::Command::Argument> m_arguments;
		std::function<void(const Structures::Message&, std::unordered_map<std::string, Argument>)> m_callback;
	};
}