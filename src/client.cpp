#include "client.hpp"

#include "collections/collection.hpp"

#include "structures/channels/textchannel.hpp"
#include "structures/user.hpp"

namespace Ethyme
{
	Client::Client(const std::string& token, bool const& useCommands, uint32_t const& intents)
		: m_token{ token }
		, m_connectionState{ ConnectionState::Disconnected }
		, m_heartbeatInterval{ 0 }
		, m_sequenceNumber{ 0 }
		, m_user{ Structures::User(nlohmann::json::parse(cpr::Get(
			cpr::Url(Constants::API::CurrentUser),
			cpr::Header{ { "Authorization", m_token } }
		).text), *this) }
		, m_commands{}
		, m_channels{ *this, Constants::API::Channels }
		, m_users{ *this, Constants::API::Users }
		, m_guilds{ *this, Constants::API::Guilds }
		, m_intents{ intents }
	{
		if (useCommands)
			SetupCommandHandler();
	}

	const websocketpp::lib::error_code& Client::ErrorCode() const { return ec; }
	const std::string& Client::Token() const { return m_token; }
	const Structures::User& Client::User() const { return m_user; }
	Collections::Collection<Structures::Channel>& Client::Channels() { return m_channels; }
	Collections::Collection<Structures::Guild>& Client::Guilds() { return m_guilds; }
	Collections::Collection<Structures::User>& Client::Users() { return m_users; }
	void Client::AddCommand(const std::string& name, Command command) { m_commands[name] = command; }

	const std::string& Client::AddHandler(EventType eventType, std::function<cppcoro::task<>(Events::Event&)> callback, const std::string& id)
	{
		Logger::Debug("New event handler added: " + id);
		m_eventsHandlers[eventType][id] = callback;
		return id;
	}

	void Client::SetPrefix(const std::string& prefix)
	{
		m_prefix = prefix;
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
		Logger::Debug("Starting client");
		try
		{
			m_ws.clear_access_channels(websocketpp::log::alevel::all);

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
			Logger::Error("Websocket error");
			throw e;
		}
	}
}