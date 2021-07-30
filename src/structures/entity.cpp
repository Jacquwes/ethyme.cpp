#include "structures/entity.hpp"

namespace Ethyme::Structures
{
	Entity::Entity(std::string const& id, std::shared_ptr<Ethyme::Client> client, bool const& partial, nlohmann::json const& data)
		: m_id(id)
		, m_client(client)
		, m_partial{ partial }
		, m_data{ data.is_array() ? data[0] : data }
	{}
}