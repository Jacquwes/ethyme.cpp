#pragma once

#include "common.hpp"
#include "constants.hpp"

#include "events/event.hpp"
#include "events/messagecreate.hpp"

#include "structures/message.hpp"
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

		Client(const std::string& token);

		const std::string& addHandler(EventType, std::function<void(std::shared_ptr<const Events::Event>)> callback, const std::string& id = GenerateRandomId());
		void Start();

		const websocketpp::lib::error_code& ErrorCode();
		const std::string& Token();
		std::shared_ptr<Structures::User> User();

	private:
		enum Opcodes
		{
			Dispatch,
			Heartbeat,
			Identify,
			Hello = 10,
		};

		static std::string GenerateRandomId();

		std::unordered_map<EventType, std::unordered_map<std::string, std::function<void(std::shared_ptr<const Events::Event>)>>> m_eventsHandlers;

		std::string m_token;
		std::shared_ptr<Structures::User> m_user;

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