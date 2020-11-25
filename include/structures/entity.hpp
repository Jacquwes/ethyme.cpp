#pragma once

#include "../common.hpp"
#include "snowflake.hpp"

namespace Ethyme { class Client; }

namespace Ethyme::Structures
{
	class Entity
	{
	public:
		Entity(const std::string& id);
		virtual ~Entity() = default;

		const Snowflake& Id();
	private:
		Snowflake m_id;
	};
}