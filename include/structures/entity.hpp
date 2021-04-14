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
		Entity(std::string const& id, Ethyme::Client& client, bool const& partial = false, nlohmann::json const& data = {});
		/**
		 * @brief Inheritable
		*/
		virtual ~Entity() = default;

		/**
		 * @brief Entity's ID
		 * @return Entity's ID
		*/
		constexpr inline Snowflake const& Id() const { return m_id; }
		/**
		 * @brief Client's instance
		 * @return Client's instance
		*/
		constexpr inline Ethyme::Client& Client() const { return m_client; }

		constexpr inline virtual void Parse(nlohmann::json const& data = {}) {}

		constexpr inline bool const& Partial() const { return m_partial; }
		/**
		 * @brief Use this Entity as something else
		 * @tparam T New type
		 * @return This
		*/
		template<typename T>
		constexpr inline T& As() const
		{
			return (T&)*this;
		}

		constexpr inline nlohmann::json& Data() { return m_data; }

	private:
		nlohmann::json m_data;
		Snowflake m_id;
		Ethyme::Client& m_client;
		bool m_partial;
	};
}