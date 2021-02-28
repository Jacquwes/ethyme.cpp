#pragma once

#include "collections/collection.hpp"
#include "common.hpp"
#include "structures/entity.hpp"
#include "structures/member.hpp"
#include "structures/role.hpp"

namespace Ethyme
{
	class Client;
}

namespace Ethyme::Structures
{
	class Channel;

	class Guild : public Entity
	{
	public:
		Guild(nlohmann::json const& data, Ethyme::Client const& client);

		Collections::Collection<std::reference_wrapper<Channel>> const& Channels() const;
		Collections::Collection<Member> const& Members() const;
		std::string const& Name() const;
		Member const& Owner() const;
		Collections::Collection<Role> const& Roles() const;

	private:
		Collections::Collection<std::reference_wrapper<Channel>> m_channels;
		Collections::Collection<Member> m_members;
		std::string m_name;
		std::string m_ownerId;
		Collections::Collection<Role> m_roles;
	};
}