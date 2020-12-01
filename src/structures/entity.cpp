#include "structures/entity.hpp"

namespace Ethyme::Structures
{
	Entity::Entity(const std::string& id, const Ethyme::Client& client)
		: m_id(id)
		, m_client(client)
	{}

	const Client& Entity::Client() const { return m_client; }
	const Snowflake& Entity::Id() const { return m_id; }
}