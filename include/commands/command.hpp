#pragma once

#include "common.hpp"

namespace Ethyme::Structures
{
	class Message;
}

namespace Ethyme
{
	/**
	 * @brief Represents a bot command. Used by the command manager.
	*/
	class Command
	{
	public:
		/**
		 * @brief Specifies the type of a command.
		*/
		enum class ArgumentType
		{
			Bool,
			String,
			Int,
			Double,
		};
		/**
		 * @brief Represents a command argument.
		*/
		struct Argument
		{
			/**
			 * @brief Specifies whether the argument can be ignored or not.
			*/
			bool Required = false;
			/**
			 * @brief Specifies the type of the argument.
			*/
			ArgumentType Type = ArgumentType::String;
			/**
			 * @brief Value of the argument when the command is executed by an User.
			*/
			std::optional<std::variant<bool, std::string, int, double>> Value = std::nullopt;
		};

		/**
		 * @brief Default constructor.
		*/
		Command() = default;
		/**
		 * @brief Create a command directly with a callback and its arguments.
		 * @param callback Function called when the command is triggered.
		 * @param args Command's arguments.
		*/
		Command(const std::function<cppcoro::task<>(std::shared_ptr<Structures::Message>& message, std::unordered_map<std::string, Argument> arguments)>& callback, std::unordered_map<std::string, Command::Argument> args);
		/**
		 * @brief This destructor is here to allow you to inherit this class.
		*/
		virtual ~Command() = default;

		/**
		 * @brief Returns the current instance of the Command's default arguments.
		 * @return Command's arguments.
		*/
		std::unordered_map<std::string, Argument>& Arguments();
		/**
		 * @brief Add or modify a Command's Argument
		 * @param name Name of the Argument
		 * @param value Argument instance
		*/
		void SetArgument(const std::string& name, std::optional<std::variant<bool, std::string, int, double>> value);
		/**
		 * @brief Function called when the Command is triggered.
		 * @return A function
		*/
		const std::function<cppcoro::task<>(std::shared_ptr<Structures::Message>& message, std::unordered_map<std::string, Argument> arguments)>& Callback() const;

	protected:
		std::unordered_map<std::string, Argument> arguments;

	private:
		std::function<cppcoro::task<>(std::shared_ptr<Structures::Message>& message, std::unordered_map<std::string, Argument> arguments)> m_callback;
	};
}