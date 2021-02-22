#pragma once

#include "../common.hpp"
#include "snowflake.hpp"

namespace Ethyme
{
	class Client;
}

namespace Ethyme::Structures
{
	/**
	 * @brief Doll class. Inherited by all Discord entities.
	*/
	class Entity
	{
	public:
		/**
		 * @brief Constructor
		 * @param id ID of the entity
		 * @param client Client's instance
		*/
		Entity(const std::string& id, const Ethyme::Client& client);
		/**
		 * @brief Inheritable
		*/
		virtual ~Entity() = default;

		/**
		 * @brief Entity's ID
		 * @return Entity's ID
		*/
		const Snowflake& Id() const;
		/**
		 * @brief Client's instance
		 * @return Client's instance
		*/
		const Ethyme::Client& Client() const;
		/**
		 * @brief Use this Entity as something else
		 * @tparam T New type
		 * @return This
		*/
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