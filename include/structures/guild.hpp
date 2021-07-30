#pragma once

#include "collections/collection.hpp"
#include "common.hpp"
#include "structures/entity.hpp"
#include "structures/member.hpp"
#include "structures/role.hpp"

namespace Ethyme
{
	class Client;

	namespace Structures
	{
		namespace Channels
		{
			class Channel;
		}

		class Guild : public Entity
		{
		public:
			Guild(nlohmann::json const& data, std::shared_ptr<Ethyme::Client> client, bool const& parse = true);

			Collections::Collection<std::shared_ptr<Channels::Channel>>& Channels();
			Collections::Collection<std::shared_ptr<Member>>& Members();
			std::string const& Name() const;
			std::shared_ptr<Member>& Owner();
			Collections::Collection<std::shared_ptr<Role>>& Roles();

			void Parse(nlohmann::json const& data = {}) override;

		private:
			Collections::Collection<std::shared_ptr<Channels::Channel>> m_channels;
			Collections::Collection<std::shared_ptr<Member>> m_members;
			std::string m_name;
			std::string m_ownerId;
			Collections::Collection<std::shared_ptr<Role>> m_roles;
		};
	}
}