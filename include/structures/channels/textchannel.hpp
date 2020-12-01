#pragma once

#include "common.hpp"
#include "structures/channel.hpp"

namespace Ethyme::Structures
{
	class TextChannel : public Channel
	{
	public:
		TextChannel(const nlohmann::json& data, const Ethyme::Client& client);

		void Send(const std::string& content) const;
	};
}
