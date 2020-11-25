#include "structures/snowflake.hpp"

namespace Ethyme::Structures
{
	Snowflake::Snowflake(const std::string& id)
		: m_id(id)
	{}

	Snowflake::operator const std::string()& { return m_id; }
	Snowflake::operator const uint64_t()& { return std::stoull(m_id); }
}