#include "structures/entity.hpp"

namespace Ethyme::Structures
{
	Entity::Entity(std::string const& id, Ethyme::Client& client, bool const& partial, nlohmann::json const& data)
		: m_id(id)
		, m_client(client)
		, m_partial{ partial }
		, m_data{ data }
	{}
}