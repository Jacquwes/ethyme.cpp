#include "client.hpp"

namespace Ethyme
{
	void Client::SendHeartbeat(websocketpp::connection_hdl handler)
	{
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
			if (payload["t"].get<std::string>() == "MESSAGE_CREATE")
			{
				std::shared_ptr<const Events::MessageCreate> msg(new Events::MessageCreate(payload["d"]));
				for (auto& handler : m_eventsHandlers[EventType::MessageCreate])
					handler.second(
						std::dynamic_pointer_cast<const Events::Event>(msg)
					);
			}
			break;
		}
		case Hello:
		{
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
			id["d"]["intents"] = (1 << 9);
			id["d"]["properties"]["$os"] = "windows";
			id["d"]["properties"]["$browser"] = "ethyme.cpp";
			id["d"]["properties"]["$browser"] = "ethyme.cpp";

			m_ws.send(handler, id.dump(), websocketpp::frame::opcode::text, ec);
			
			break;
		}
		default:
		{
			std::cout << "Unhandled payload received:" << std::to_string(opcode) << std::endl;
			break;
		}
		}
	}
}