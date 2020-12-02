#include "client.hpp"

#include "structures/channels/textchannel.hpp"
#include "structures/collection.hpp"
#include "structures/user.hpp"

namespace Ethyme
{
	Client::Client(const std::string& token, bool useCommands)
		: m_token(token)
		, m_connectionState(ConnectionState::Disconnected)
		, m_heartbeatInterval(0)
		, m_sequenceNumber(0)
		, m_user(Structures::User(nlohmann::json::parse(cpr::Get(
			cpr::Url(Constants::API::CurrentUser),
			cpr::Header{ { "Authorization", m_token } }
		).text), *this))
	{
		if (useCommands)
		{
			AddHandler(EventType::MessageCreate,
				[&](const Ethyme::Events::Event& event)
				{
					auto& message = (*(Events::MessageCreate*)&event).Message();

					if (message.Content().rfind(m_prefix, 0)) return;

					std::vector<std::string> arguments = { "" };
					for (int i = m_prefix.size(); i < message.Content().size(); i++)
						if (message.Content()[i] == ' ')
							arguments.push_back("");
						else
							arguments.back().push_back(message.Content()[i]);

					if (arguments.size() == 0) return;

					std::string commandName = arguments[0];
					arguments.erase(arguments.begin());

					auto command = std::find_if(m_commands.begin(), m_commands.end(),
						[&](const auto& command_)
						{
							return command_.first == commandName;
						});
					
					if (command != m_commands.end())
					{
						std::unordered_map<std::string, Commands::Command::Argument> parsedArguments = command->second.Arguments();
						std::string currentArgument;
						for (auto& argument : arguments)
						{
							if (!argument.rfind("--", 0))
							{
								if (!parsedArguments.count(argument.substr(2)))
								{
									std::string errorMessage = "<@" + message.Author().Id().ToString() + ">, argument \"" + argument.substr(2) + "\" unknown.";
									message.Channel().Send(errorMessage);
									return;
								}
								else
									currentArgument = argument.substr(2);
							}
							else
							{
								using t = Commands::Command::Argument::ArgumentType;
								switch (parsedArguments[currentArgument].Type)
								{
								case t::Bool:
								{
									std::transform(argument.begin(), argument.end(), argument.begin(), [&](auto c) { return std::tolower(c); });
									if (
										argument == "n" ||
										argument == "no" ||
										argument == "false" ||
										argument == "f"
										)
										parsedArguments[currentArgument].Value = false;
									else if (
										argument == "y" ||
										argument == "yes" ||
										argument == "true" ||
										argument == "t"
										)
										parsedArguments[currentArgument].Value = true;
									else
									{
										message.Channel().Send("<@" + message.Author().Id().ToString() + ">, \"" + argument + "\" is not a valid boolean argument.");
										return;
									}
									break;
								}
								case t::String:
								{
									std::get<std::string>(parsedArguments[currentArgument].Value) += argument + " ";
									break;
								}
								}
							}
						}
						command->second.Execute(message, parsedArguments);
					}


				}, "commandHandler");
		}
	}

	const websocketpp::lib::error_code& Client::ErrorCode() const { return ec; }
	const std::string& Client::Token() const { return m_token; }
	const Structures::User& Client::User() const { return m_user; }

	const Structures::Collection<Structures::Channel>& Client::Channels() const
	{
		return m_channels;
	}

	const Structures::Collection<Structures::User>& Client::Users() const
	{
		return m_users;
	}

	void Client::AddCommand(const std::string& name, const Commands::Command& command)
	{
		m_commands[name] = command;
	}

	const std::string& Client::AddHandler(EventType eventType, std::function<void(const Events::Event&)> callback, const std::string& id)
	{
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