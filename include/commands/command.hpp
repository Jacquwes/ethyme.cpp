#pragma once

#include "common.hpp"

namespace Ethyme::Structures
{
	class Message;
}

namespace Ethyme
{
	class Command
	{
	public:
		enum class ArgumentType
		{
			Bool,
			String,
			Int,
			Double,
		};
		struct Argument
		{
			bool Required = false;
			ArgumentType Type = ArgumentType::String;
			std::optional<std::variant<bool, std::string, int, double>> Value = std::nullopt;
		};

		Command() = default;
		Command(const std::function<void(const Structures::Message& message, std::unordered_map<std::string, Argument> arguments)>& callback, std::unordered_map<std::string, Command::Argument> args);
		virtual ~Command() = default;

		std::unordered_map<std::string, Argument>& Arguments();
		void SetArgument(const std::string& name, std::optional<std::variant<bool, std::string, int, double>> value);
		const std::function<void(const Structures::Message& message, std::unordered_map<std::string, Argument> arguments)>& Callback() const;

	protected:
		std::unordered_map<std::string, Argument> arguments;

	private:
		std::function<void(const Structures::Message& message, std::unordered_map<std::string, Argument> arguments)> m_callback;
	};
}