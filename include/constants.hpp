#pragma once

#include "common.hpp"

namespace Ethyme::Constants
{
	const std::string GatewayUri = "wss://gateway.discord.gg/";

	namespace API
	{
		const std::string Base = "https://discord.com/api/v8";
		const std::string Channels = Base + "/channels/";
		const std::string Guilds = Base + "/guilds/";

		const std::string Users = Base + "/users";
		const std::string CurrentUser = Users + "/@me";
	}

	namespace Intents
	{
		enum
		{
			Guilds					= 1 << 0,
			GuildMembers			= 1 << 1,
			GuildBans				= 1 << 2,
			GuildEmojis				= 1 << 3,
			GuildIntegrations		= 1 << 4,
			GuildWebhooks			= 1 << 5,
			GuildInvites			= 1 << 6,
			GuildVoiceStates		= 1 << 7,
			GuildPresences			= 1 << 8,
			GuildMessages			= 1 << 9,
			GuildMessageReactions	= 1 << 10,
			GuildMessageTyping		= 1 << 11,
			DirectMessages			= 1 << 12,
			DirectMessageReactions	= 1 << 13,
			DirectMessageTyping		= 1 << 14,
		};
		inline uint32_t const& Default = 0x3fff ^ 2 ^ 0x100;
	}

	namespace Permissions
	{
		enum
		{
			CreateInstantInvite = 1 << 0,
			KickMembers = 1 << 1,
			BanMembers = 1 << 2,
			Administrator = 1 << 3,
			ManageChannels = 1 << 4,
			ManageGuild = 1 << 5,
			AddReactions = 1 << 6,
			ViewAuditLog = 1 << 7,
			PrioritySpeaker = 1 << 8,
			Stream = 1 << 9,
			ViewChannel = 1 << 10,
			SendMessages = 1 << 11,
			SendTTSMessages = 1 << 12,
			ManageMessages = 1 << 13,
			EmbedLinks = 1 << 14,
			AttachFiles = 1 << 15,
			ReadMessageHistory = 1 << 16,
			MentionEveryone = 1 << 17,
			UseExternalEmojis = 1 << 18,
			ViewGuildInsights = 1 << 19,
			Connect = 1 << 20,
			Speak = 1 << 21,
			MuteMembers = 1 << 22,
			DeafenMembers = 1 << 23,
			MoveMembers = 1 << 24,
			/**
			 * @brief VoiceActivityDetection
			*/
			UseVAD = 1 << 25,
			ChangeNickname = 1 << 26,
			ManageNicknames = 1 << 27,
			ManageRoles = 1 << 28,
			ManageWebhooks = 1 << 29,
			ManageEmojis = 1 << 30
		};
	}
}