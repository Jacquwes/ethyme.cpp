#pragma once

#include "common.hpp"

namespace Ethyme::Structures
{
	class Snowflake
	{
	public:
		Snowflake(const std::string& id);
		virtual ~Snowflake() = default;

		operator const std::string()&;
		operator const uint64_t()&;

	private:
		std::string m_id;
	};
}