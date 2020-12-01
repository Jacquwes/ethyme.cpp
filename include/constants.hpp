#pragma once

#include "common.hpp"

namespace Ethyme::Constants
{
	const std::string GatewayUri = "wss://gateway.discord.gg/";

	namespace API
	{
		const std::string Base = "https://discord.com/api/v8";
		const std::string Channels = Base + "/channels/";
		const std::string Guilds = Base + "/guilds/";

		const std::string Users = Base + "/users";
		const std::string CurrentUser = Users + "/@me";
	}
}