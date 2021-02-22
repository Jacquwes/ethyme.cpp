#pragma once

#include "common.hpp"
#include "structures/entity.hpp"

namespace Ethyme::Structures
{
	/**
	 * @brief Doll class. Inherited by all Discord channels classes.
	*/
	class Channel : public Entity
	{
	public:
		enum class ChannelType;

		/**
		 * @brief Channel constructor
		 * @param channelType Type of the channel
		 * @param id Id of the channel
		 * @param client You guessed it right, Client's instance
		*/
		Channel(const ChannelType& channelType, const std::string& id, const Ethyme::Client& client);
		/**
		 * @brief Channel's type
		 * @return Channel's type
		*/
		const ChannelType& Type() const;

	private:
		ChannelType m_channelType;
	};
}
