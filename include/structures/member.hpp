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
		Member(nlohmann::json const& data, Ethyme::Client& client);

		std::optional<std::string> const& Nickname() const;
		Collections::Collection<Role, true>& Roles();
		Structures::User& User();

	private:
		std::optional<std::string> m_nickname;
		Collections::Collection<Role, true> m_roles;
		Structures::User& m_user;
	};
}