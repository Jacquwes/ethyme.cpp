#pragma once

#include "common.hpp"

namespace Ethyme::Structures
{
	/**
	 * @brief Discord's ID system
	*/
	class Snowflake
	{
	public:
		Snowflake(const std::string& id);
		virtual ~Snowflake() = default;

		/**
		 * @brief Returns the ID as a string
		*/
		operator const std::string() const&;
		/**
		 * @brief Returns the ID as an integer
		*/
		operator const uint64_t() const&;

		/**
		 * @brief Returns the ID as a string
		*/
		const std::string& ToString() const;

	private:
		std::string m_id;
	};
}