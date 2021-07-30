#pragma once

#include "common.hpp"
#include "constants.hpp"
#include "logger.hpp"

#include "collections/collection.hpp"
#include "commands/command.hpp"

#include "events/event.hpp"
#include "events/guildcreate.hpp"
#include "events/messagecreate.hpp"
#include "events/ready.hpp"

#include "structures/channels/channel.hpp"
#include "structures/exception.hpp"
#include "structures/guild.hpp"
#include "structures/user.hpp"

namespace Ethyme
{
	/**
	 * @brief Possible events types
	*/
	enum class EventType
	{
		GuildCreate,
		MessageCreate,
		Ready
	};

	/**
	 * @brief Represent an Ethyme Client. Use it to communicate with Discord.
	*/
	class Client : public std::enable_shared_from_this<Client>
	{
	public:
		/**
		 * @brief State of the connection with Discord.
		*/
		enum class ConnectionState
		{
			Connected,
			Connecting,
			Disconnected,
		};

		/**
		 * @brief Client's constructor
		 * @param token Any Discord account's token
		 * @param useCommands Whether you want to use the built-in command handler or not
		*/
		Client(std::string const& token, bool const& useCommands = true, uint32_t const& intents = Constants::Intents::Default);

		/**
		 * @brief Add a new Command to the command handler.
		 * @param name Name of the command. Will be used to trigger the command.
		 * @param command Command instance.
		*/
		Command& AddCommand(std::string const& name, Command command);
		/**
		 * @brief Add a handler to the Client.
		 * @param eventType Type of Event to listen to.
		 * @param callback Function called when the Event will be triggered.
		 * @param id ID of the handler. In the future, will be used to managed short-term listerners in the future.
		 * @return ID of the handler.
		*/
		std::string const& AddHandler(EventType eventType, std::function<cppcoro::task<>(Events::Event&)> callback, std::string const& id = GenerateRandomId());
		/**
		 * @brief Set the prefix used for commands.
		 * @param prefix Prefix to use.
		*/
		void SetPrefix(std::string const& prefix);
		/**
		 * @brief Connect the Client to Discord.
		*/
		void Start();

		std::unordered_map<std::string, Command> const& Commands() const;
		/**
		 * @brief You may use it for further debugging.
		 * @return Error code.
		*/
		websocketpp::lib::error_code const& ErrorCode() const;
		/**
		 * @brief Token used by the Client.
		 * @return Token used by the Client.
		*/
		std::string const& Token() const;
		/**
		 * @brief Account of the Client.
		 * @return Account of the Client.
		*/
		std::shared_ptr<Structures::User> const& User() const;

		/**
		 * @brief Collection of Channel available to the Client.
		 * @return Channels
		*/
		Collections::Collection<std::shared_ptr<Structures::Channels::Channel>>& Channels();
		/**
		 * @brief Collection of Guild available to the Client.
		 * @return Guilds
		*/
		Collections::Collection<std::shared_ptr<Structures::Guild>>& Guilds();
		/**
		 * @brief Collection of User available to the Client.
		 * @return Users
		*/
		Collections::Collection<std::shared_ptr<Structures::User>>& Users();
		
		std::shared_ptr<Structures::Channels::Channel> const& UnknownChannel() const;

	private:
		enum Opcodes
		{
			Dispatch,
			Heartbeat,
			Identify,
			Hello = 10,
		};

		void SetupCommandHandler();
		std::unordered_map<std::string, Command> m_commands;
		std::shared_ptr<Client> m_shared;

		Collections::Collection<std::shared_ptr<Structures::Channels::Channel>> m_channels;
		Collections::Collection<std::shared_ptr<Structures::Guild>> m_guilds;
		Collections::Collection<std::shared_ptr<Structures::User>> m_users;
		std::shared_ptr<Structures::Channels::Channel> m_unknownChannel;

		static std::string GenerateRandomId();

		std::unordered_map<EventType, std::unordered_map<std::string, std::function<cppcoro::task<>(Events::Event&)>>> m_eventsHandlers;

		uint32_t m_intents;
		std::string m_prefix;
		std::string m_token;
		std::shared_ptr<Structures::User> m_user;

		websocketpp::client<websocketpp::config::asio_tls_client> m_ws;
		websocketpp::lib::error_code ec;
		std::shared_ptr<void> m_handler;
		
		uint32_t m_sequenceNumber;
		uint32_t m_heartbeatInterval;
		std::thread m_heartbeatSender;
		void SendHeartbeat(websocketpp::connection_hdl);

		ConnectionState m_connectionState;

		std::shared_ptr<websocketpp::lib::asio::ssl::context> OnTlsInit(const char*, websocketpp::connection_hdl);
		void OnWebsocketMessage(websocketpp::client<websocketpp::config::asio_tls_client>*, websocketpp::connection_hdl, websocketpp::config::asio_client::message_type::ptr);
	};
}