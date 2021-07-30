#include "client.hpp"

#include "collections/collection.hpp"

#include "structures/channels/textchannel.hpp"
#include "structures/user.hpp"

namespace Ethyme
{
	typedef websocketpp::client<websocketpp::config::asio_tls_client> WebsocketClient;
	typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;
	typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

	using websocketpp::lib::placeholders::_1;
	using websocketpp::lib::placeholders::_2;
	using websocketpp::lib::bind;

	Client::Client(const std::string& token, bool const& useCommands, uint32_t const& intents)
		: m_shared{ std::shared_ptr<Client>(this) }
		, m_token { token }
		, m_connectionState{ ConnectionState::Disconnected }
		, m_heartbeatInterval{ 0 }
		, m_sequenceNumber{ 0 }
		, m_commands{}
		, m_channels{ m_shared, Constants::API::Channels }
		, m_users{ m_shared, Constants::API::Users }
		, m_guilds{ m_shared, Constants::API::Guilds }
		, m_intents{ intents }
		, m_unknownChannel{ std::make_shared<Structures::Channels::Channel>(nlohmann::json(), m_shared) }

	{
		auto request = cpr::Get(
			cpr::Url(Constants::API::CurrentUser),
			cpr::Header{ { "Authorization", m_token } }
		);
		
		if (request.status_code == 401)
			throw Exception("This token is invalid.", Exception::ErrorCode::InvalidToken);

		m_user = std::make_shared<Structures::User>(nlohmann::json::parse(request.text), m_shared);

		if (useCommands)
			SetupCommandHandler();
	}

	websocketpp::lib::error_code const& Client::ErrorCode() const { return ec; }
	std::string const& Client::Token() const { return m_token; }
	std::shared_ptr<Structures::User> const& Client::User() const { return m_user; }
	Collections::Collection<std::shared_ptr<Structures::Channels::Channel>>& Client::Channels() { return m_channels; }
	Collections::Collection<std::shared_ptr<Structures::Guild>>& Client::Guilds() { return m_guilds; }
	Collections::Collection<std::shared_ptr<Structures::User>>& Client::Users() { return m_users; }
	std::shared_ptr<Structures::Channels::Channel> const& Client::UnknownChannel() const { return m_unknownChannel; }
	
	Command& Client::AddCommand(const std::string& name, Command command) { m_commands[name] = command; return m_commands[name]; }
	const std::string& Client::AddHandler(EventType eventType, std::function<cppcoro::task<>(Events::Event&)> callback, const std::string& id)
	{
		Logger::Debug("New event handler added: " + id);
		m_eventsHandlers[eventType][id] = callback;
		return id;
	}
	void Client::SetPrefix(const std::string& prefix) { m_prefix = prefix; }
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

	std::unordered_map<std::string, Command> const& Client::Commands() const { return m_commands; }
}