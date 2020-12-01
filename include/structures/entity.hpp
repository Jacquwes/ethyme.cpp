#pragma once

#include "../common.hpp"
#include "snowflake.hpp"

namespace Ethyme
{
	class Client;
}

namespace Ethyme::Structures
{
	class Entity
	{
	public:
		Entity(const std::string& id, const Ethyme::Client& client);
		virtual ~Entity() = default;

		const Snowflake& Id() const;
		const Ethyme::Client& Client() const;
		template<typename T>
		inline T& As() const
		{
			return (T&)*this;
		}

	private:
		Snowflake m_id;
		const Ethyme::Client& m_client;
	};
}