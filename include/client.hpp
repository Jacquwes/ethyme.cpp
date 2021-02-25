#pragma once

#include "common.hpp"
#include "constants.hpp"
#include "logger.hpp"

#include "collections/collection.hpp"
#include "commands/command.hpp"

#include "events/event.hpp"
#include "events/messagecreate.hpp"
#include "events/ready.hpp"

#include "structures/channels/channel.hpp"
#include "structures/user.hpp"

namespace Ethyme
{
	typedef websocketpp::client<websocketpp::config::asio_tls_client> WebsocketClient;
	typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;
	typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

	using websocketpp::lib::placeholders::_1;
	using websocketpp::lib::placeholders::_2;
	using websocketpp::lib::bind;

	/**
	 * @brief Possible events types
	*/
	enum class EventType
	{
		MessageCreate,
		Ready
	};

	/**
	 * @brief Represent an Ethyme Client. Use it to communicate with Discord.
	*/
	class Client
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
		Client(const std::string& token, bool useCommands = true);

		/**
		 * @brief Add a new Command to the command handler.
		 * @param name Name of the command. Will be used to trigger the command.
		 * @param command Command instance.
		*/
		void AddCommand(const std::string& name, Command command);
		/**
		 * @brief Add a handler to the Client.
		 * @param eventType Type of Event to listen to.
		 * @param callback Function called when the Event will be triggered.
		 * @param id ID of the handler. In the future, will be used to managed short-term listerners in the future.
		 * @return ID of the handler.
		*/
		const std::string& AddHandler(EventType eventType, std::function<cppcoro::task<>(Events::Event&)> callback, const std::string& id = GenerateRandomId());
		/**
		 * @brief Set the prefix used for commands.
		 * @param prefix Prefix to use.
		*/
		void SetPrefix(const std::string& prefix);
		/**
		 * @brief Connect the Client to Discord.
		*/
		void Start();

		/**
		 * @brief You may use it for further debugging.
		 * @return Error code.
		*/
		const websocketpp::lib::error_code& ErrorCode() const;
		/**
		 * @brief Token used by the Client.
		 * @return Token used by the Client.
		*/
		const std::string& Token() const;
		/**
		 * @brief Account of the Client.
		 * @return Account of the Client.
		*/
		const Structures::User& User() const;

		/**
		 * @brief Collection of Channel available to the Client.
		 * @return Channels
		*/
		Collections::Collection<Structures::Channel> const& Channels() const;
		/**
		 * @brief Collection of User available to the Client.
		 * @return Users
		*/
		Collections::Collection<Structures::User> const& Users() const;

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

		Collections::Collection<Structures::Channel> m_channels;
		Collections::Collection<Structures::User> m_users;

		static std::string GenerateRandomId();

		std::unordered_map<EventType, std::unordered_map<std::string, std::function<cppcoro::task<>(Events::Event&)>>> m_eventsHandlers;

		std::string m_prefix;
		std::string m_token;
		Structures::User m_user;

		WebsocketClient m_ws;
		websocketpp::lib::error_code ec;
		std::shared_ptr<void> m_handler;
		
		uint32_t m_sequenceNumber;
		uint32_t m_heartbeatInterval;
		std::thread m_heartbeatSender;
		void SendHeartbeat(websocketpp::connection_hdl);

		ConnectionState m_connectionState;

		context_ptr OnTlsInit(const char*, websocketpp::connection_hdl);
		void OnWebsocketMessage(WebsocketClient*, websocketpp::connection_hdl, message_ptr);
	};
}