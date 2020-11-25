#include "client.hpp"

namespace Ethyme
{
	Client::Client(const std::string& token)
		: m_token(token)
		, m_connectionState(ConnectionState::Disconnected)
		, m_heartbeatInterval(0)
		, m_sequenceNumber(0)
	{}

	const websocketpp::lib::error_code& Client::ErrorCode() { return ec; }
	const std::string& Client::Token() { return m_token; }
	std::shared_ptr<Structures::User> Client::User() { return m_user; }

	const std::string& Client::addHandler(EventType eventType, std::function<void(std::shared_ptr<const Events::Event>)> callback, const std::string& id)
	{
		m_eventsHandlers[eventType][id] = callback;
		return id;
	}

	std::string Client::GenerateRandomId()
	{
		std::string id = "";
		for (int i = 0; i < 10; i++)
		{
			std::random_device rd;
			std::uniform_int_distribution<int> dist('A', ((int)'Z'));
			int n = dist(rd);
			id.push_back(n & 1 ? n : n + ('a' - 'A'));
		}
		return id;
	}

	context_ptr Client::OnTlsInit(const char* hostname, websocketpp::connection_hdl)
	{
		context_ptr ctx = websocketpp::lib::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::sslv23);
		return ctx;
	}

	void Client::Start()
	{
		try
		{
			m_ws.set_access_channels(websocketpp::log::alevel::all);
			m_ws.clear_access_channels(websocketpp::log::alevel::frame_payload);

			m_ws.init_asio();
			m_ws.set_message_handler(websocketpp::lib::bind(&Client::OnWebsocketMessage, this, &m_ws, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
			m_ws.set_tls_init_handler(websocketpp::lib::bind(&Client::OnTlsInit, this, Constants::GatewayUri.c_str(), websocketpp::lib::placeholders::_1));

			WebsocketClient::connection_ptr connection = m_ws.get_connection(Constants::GatewayUri, ec);

			if (ec)
				throw websocketpp::exception(ec);

			m_ws.connect(connection);
			m_ws.run();
		}
		catch (const websocketpp::exception& e)
		{
			throw e;
		}
	}
}