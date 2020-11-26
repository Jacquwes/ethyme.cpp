#pragma once

#include "../common.hpp"
#include "snowflake.hpp"

DefineClient

namespace Ethyme::Structures
{
	class Entity
	{
	public:
		Entity(const std::string& id, const std::shared_ptr<Ethyme::Client>& client);
		virtual ~Entity() = default;

		const Snowflake& Id() const;
	private:
		Snowflake m_id;

		ClientMembers
	};
}