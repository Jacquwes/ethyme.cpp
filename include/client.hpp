#pragma once

#include "common.hpp"
#include "constants.hpp"

#include "commands/command.hpp"

#include "events/event.hpp"
#include "events/messagecreate.hpp"

#include "structures/collection.hpp"
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

	enum class EventType
	{
		MessageCreate,
	};

	class Client
	{
	public:
		enum class ConnectionState
		{
			Connected,
			Connecting,
			Disconnected,
		};

		Client(const std::string& token, bool useCommands = true);

		void AddCommand(const std::string& name, Command command);
		const std::string& AddHandler(EventType, std::function<void(const Events::Event&)> callback, const std::string& id = GenerateRandomId());
		void SetPrefix(const std::string& prefix);
		void Start();

		const websocketpp::lib::error_code& ErrorCode() const;
		const std::string& Token() const;
		const Structures::User& User() const;

		const Structures::Collection<Structures::Channel>& Channels() const;
		const Structures::Collection<Structures::User>& Users() const;

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

		Structures::Collection<Structures::Channel> m_channels;
		Structures::Collection<Structures::User> m_users;

		static std::string GenerateRandomId();

		std::unordered_map<EventType, std::unordered_map<std::string, std::function<void(const Events::Event&)>>> m_eventsHandlers;

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