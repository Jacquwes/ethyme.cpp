#pragma once

#include "common.hpp"
#include "structures/entity.hpp"

namespace Ethyme
{
	class Client;
}

namespace Ethyme::Structures
{
	class Role : public Entity
	{
	public:
		Role(nlohmann::json const& data, Ethyme::Client& client);

		uint32_t const& Color() const;
		std::string const& Name() const;
		uint32_t const& Permissions() const;
		uint16_t const& Position() const;

	private:
		uint32_t m_color;
		std::string m_name;
		uint32_t m_permissions;
		uint16_t m_position;
	};
}