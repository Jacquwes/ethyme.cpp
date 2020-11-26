#pragma once

#include "common.hpp"

namespace Ethyme::Structures
{
	class Snowflake
	{
	public:
		Snowflake(const std::string& id);
		virtual ~Snowflake() = default;

		operator const std::string() const&;
		operator const uint64_t() const&;

		const std::string& ToString() const;

	private:
		std::string m_id;
	};
}