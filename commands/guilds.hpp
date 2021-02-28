#include "ethyme.hpp"

using namespace Ethyme;

inline auto GuildsCommand = Command(
	[&](Structures::Message& message, std::unordered_map<std::string, Command::Argument> arguments) -> cppcoro::task<>
	{
		std::string guilds;

		for (
			auto guild = Collections::Collection<Structures::Guild>::Iterator(message.Client().Guilds().cbegin());
			guild != message.Client().Guilds().cend();
			guild++)
			guilds += guild->Name();

		co_await message.Channel().Send(guilds);
	}, {}
	);