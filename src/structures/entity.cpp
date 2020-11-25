#include "structures/entity.hpp"

namespace Ethyme::Structures
{
	Entity::Entity(const std::string& id)
		: m_id(id)
	{}
	const Snowflake& Entity::Id() { return m_id; }
}