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
		Member(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client);

		std::optional<std::string> const& Nickname() const;
		Collections::Collection<std::shared_ptr<Role>>& Roles();
		std::shared_ptr<Structures::User>& User();

	private:
		std::optional<std::string> m_nickname;
		Collections::Collection<std::shared_ptr<Role>> m_roles;
		std::shared_ptr<Structures::User>& m_user;
	};
}