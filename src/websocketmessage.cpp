#include "client.hpp"

#include "structures/channels/textchannel.hpp"
#include "structures/guild.hpp"
#include "structures/message.hpp"

namespace Ethyme
{
	typedef websocketpp::client<websocketpp::config::asio_tls_client> WebsocketClient;
	typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;
	typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

	using websocketpp::lib::placeholders::_1;
	using websocketpp::lib::placeholders::_2;
	using websocketpp::lib::bind;

	void Client::SendHeartbeat(websocketpp::connection_hdl handler)
	{
		Logger::Debug("Sending heartbeat");
		nlohmann::json message;
		message["op"] = Heartbeat;
		message["d"] = m_sequenceNumber;
		m_ws.send(handler, message.dump(), websocketpp::frame::opcode::text, ec);
	}

	void Client::OnWebsocketMessage(WebsocketClient* client, websocketpp::connection_hdl handler, message_ptr message)
	{
		nlohmann::json payload = nlohmann::json::parse(message->get_payload());
		uint8_t opcode = payload["op"].get<uint8_t>();

		m_handler = m_ws.get_con_from_hdl(handler, ec);

		switch (opcode)
		{
		case Dispatch:
		{
			#pragma region GuildCreate
			if (payload["t"].get<std::string>() == "GUILD_CREATE")
			{
				Logger::Debug("Received GuildCreate event");
				auto guild = std::make_shared<Structures::Guild>(payload["d"], shared_from_this(), false);
				m_guilds.Add(guild)->Parse();
				Logger::Debug(guild->Name() + " successfully cached");

				Events::GuildCreate event{ guild };
				for (auto& handler : m_eventsHandlers[EventType::GuildCreate])
					std::async([&] { cppcoro::sync_wait(handler.second(event)); });
			}
			#pragma endregion
			#pragma region MessageCreate
			else if (payload["t"].get<std::string>() == "MESSAGE_CREATE")
			{
				auto msg = std::make_shared<Structures::Message>(payload["d"], shared_from_this());
				Events::MessageCreate event{ msg };
				for (auto& handler : m_eventsHandlers[EventType::MessageCreate])
					std::async([&] { cppcoro::sync_wait(handler.second(event)); });
			}
			#pragma endregion
			#pragma region Ready
			else if (payload["t"].get<std::string>() == "READY")
			{
				Logger::Debug("Client ready");
				Events::Ready event{ shared_from_this() };
				for (auto& handler : m_eventsHandlers[EventType::Ready])
					std::async([&] { cppcoro::sync_wait(handler.second(*(Events::Event*)&event)); });
			}
			#pragma endregion
			break;
		}
		case Hello:
		{
			Logger::Debug("Client signing in");
			m_heartbeatInterval = payload["d"]["heartbeat_interval"].get<uint32_t>();
			m_connectionState = ConnectionState::Connecting;
			m_heartbeatSender = std::thread([&]()
				{
					while (m_connectionState != ConnectionState::Disconnected)
					{
						SendHeartbeat(m_handler);
						std::this_thread::sleep_for(std::chrono::milliseconds(m_heartbeatInterval));
					}
				});

			nlohmann::json id;
			id["op"] = Identify;
			id["d"]["token"] = m_token;
			id["d"]["intents"] = m_intents;
			id["d"]["properties"]["$os"] = "windows";
			id["d"]["properties"]["$browser"] = "ethyme.cpp";
			id["d"]["properties"]["$browser"] = "ethyme.cpp";

			m_ws.send(handler, id.dump(), websocketpp::frame::opcode::text, ec);
			
			break;
		}
		default:
		{
			Logger::Debug("Unhandled payload received:" + std::to_string(opcode));
			break;
		}
		}
	}
}