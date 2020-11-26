#include "structures/snowflake.hpp"

namespace Ethyme::Structures
{
	Snowflake::Snowflake(const std::string& id)
		: m_id(id)
	{}

	Snowflake::operator const std::string() const& { return m_id; }
	Snowflake::operator const uint64_t() const& { return std::stoull(m_id); }

	const std::string& Snowflake::ToString() const { return m_id; }
}