#include "structures/role.hpp"

#include "client.hpp"
#include "structures/guild.hpp"

namespace Ethyme::Structures
{
	Role::Role(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client)
		: Entity(data["id"].get<std::string>(), client)
		, m_color{ data["color"].get<uint32_t>() }
		, m_name{ data["name"].get<std::string>() }
		, m_permissions{ data["permissions"].get<uint32_t>() }
		, m_position{ data["position"].get<uint16_t>() }
	{}

	uint32_t const& Role::Color() const { return m_color; }
	std::string const& Role::Name() const { return m_name; }
	uint32_t const& Role::Permissions() const { return m_permissions; }
	uint16_t const& Role::Position() const { return m_position; }
}
