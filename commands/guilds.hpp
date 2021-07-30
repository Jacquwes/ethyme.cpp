#include "ethyme.hpp"

using namespace Ethyme;

inline auto GuildsCommand = Command(
	[&](std::shared_ptr<Structures::Message>& message, std::unordered_map<std::string, Command::Argument> arguments) -> cppcoro::task<>
	{
		std::string guilds = std::to_string(message->Client()->Guilds().Size()) + " guilds:";

		for (
			auto guild = Collections::Collection<std::shared_ptr<Structures::Guild>>::Iterator(message->Client()->Guilds().cbegin());
			guild != message->Client()->Guilds().cend();
			guild++
		)
			guilds += "\n" + (*guild)->Name();

		co_await message->Channel()->Send(guilds);
	}, {}
	);