#pragma once

#include "common.hpp"

namespace Ethyme
{
	class Logger
	{
	public:
		enum class Level
		{
			None	= 0,
			Errors	= 1,
			Infos	= 1 << 1,
			Debug	= 1 << 2,
		};

		static void SetLogLevel(uint32_t const& logLevel);

		static void Debug(std::string const& message);
		static void Error(std::string const& message);
		static void Info(std::string const& message);

		static void Log(std::string const& message, Level const& logLevel);

		inline void operator<<(std::string const& message) { Info(message); }

	private:
		inline static uint32_t m_level;
	};
}