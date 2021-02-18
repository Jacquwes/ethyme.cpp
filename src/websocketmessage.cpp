#include "client.hpp"

#include "structures/channels/textchannel.hpp"
#include "structures/message.hpp"

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
			if (payload["t"].get<std::string>() == "READY")
			{
				for (auto& guild : payload["d"]["guilds"])
				{
					auto response = cpr::Get(
						cpr::Url(Constants::API::Guilds + guild["id"].get<std::string>() + "/channels"),
						cpr::Header{ { "Authorization", m_token } }).text;
					auto& channels = nlohmann::json::parse(response);
					for (const auto& channel : channels)
						m_channels.Add(Structures::TextChannel(channel, *this).As<Structures::Channel>());
					
					Events::Ready event{ *this };
					for (auto& handler : m_eventsHandlers[EventType::Ready])
						handler.second(*(Events::Event*)&event);
				}
			}
			else if (payload["t"].get<std::string>() == "MESSAGE_CREATE" || payload["t"].get<std::string>() == "MESSAGE_UPDATE")
			{
				Events::MessageCreate event{ payload["d"], *this };
				for (auto& handler : m_eventsHandlers[EventType::MessageCreate])
					handler.second(*(Events::Event*)&event);
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