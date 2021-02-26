#pragma once

#include "common.hpp"

#include "collections/collection.hpp"
#include "structures/entity.hpp"
#include "structures/user.hpp"

namespace Ethyme
{
	class Client;
}

namespace Ethyme::Structures
{
	class Role;

	class Member : public Entity
	{
	public:
		Member(nlohmann::json const& data, Ethyme::Client const& client);

		std::optional<std::string> const& Nickname() const;
		Collections::Collection<std::reference_wrapper<Role>> const& Roles() const;
		Structures::User const& User() const;

	private:
		std::optional<std::string> m_nickname;
		Collections::Collection<std::reference_wrapper<Role>> m_roles;
		Structures::User const& m_user;
	};
}