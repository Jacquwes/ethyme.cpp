#include "structures/entity.hpp"

namespace Ethyme::Structures
{
	Entity::Entity(std::string const& id, Ethyme::Client const& client, bool const& partial)
		: m_id(id)
		, m_client(client)
		, m_partial{ partial }
	{}

	Client const& Entity::Client() const { return m_client; }
	Snowflake const& Entity::Id() const { return m_id; }
	bool const& Entity::Partial() const { return m_partial; }
}