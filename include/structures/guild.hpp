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
			Guild(nlohmann::json const& data, Ethyme::Client& client, bool const& parse = true);

			Collections::Collection<Channels::Channel, true>& Channels();
			Collections::Collection<Member>& Members();
			std::string const& Name() const;
			Member& Owner();
			Collections::Collection<Role>& Roles();

			void Parse(nlohmann::json const& data = {}) override;

		private:
			Collections::Collection<Channels::Channel, true> m_channels;
			Collections::Collection<Member> m_members;
			std::string m_name;
			std::string m_ownerId;
			Collections::Collection<Role> m_roles;
		};
	}
}