#pragma once

#include "common.hpp"
#include "structures/entity.hpp"

namespace Ethyme::Structures
{
	class Channel : public Entity
	{
	public:
		enum class ChannelType;

		Channel(const ChannelType& channelType, const std::string& id, const Ethyme::Client& client);
		const ChannelType& Type() const;

	private:
		ChannelType m_channelType;
	};
}
