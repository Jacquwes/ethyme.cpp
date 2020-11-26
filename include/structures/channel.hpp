#pragma once

#include "common.hpp"

#include "entity.hpp"

DefineClient

namespace Ethyme::Structures
{
	class Message;

	class Channel : public Entity
	{
	public:
		enum class ChannelType
		{
			Text,
			DirectMessage,
			Voice,
			Group,
			Category,
			News,
			Store,
		};

		Channel(const ChannelType& channelType, const std::string& id, const std::shared_ptr<Ethyme::Client>& client);

		const ChannelType& Type() const;

	private:
		std::string m_name;
		ChannelType m_type;
	};

	class TextChannel : public Channel
	{
	public:
		TextChannel(const nlohmann::json& data, const std::shared_ptr<Ethyme::Client>& client);

		void Send(const std::string& content) const;
	};
}