#include "logger.hpp"
#include "..\include\logger.hpp"

namespace Ethyme
{
	void Logger::SetLogLevel(uint32_t const& logLevel) { m_level = logLevel; }
	void Logger::Debug(std::string const& message) { Log(message, Level::Debug); }
	void Logger::Error(std::string const& message) { Log(message, Level::Errors); } // I know that's inconsistant but I'm tired rn
	void Logger::Info(std::string const& message) { Log(message, Level::Infos); }
	void Logger::Log(std::string const& message, Level const& logLevel)
	{
		if (!(static_cast<uint32_t>(m_level) & static_cast<uint32_t>(logLevel)))
			return;

		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		std::ostringstream time; time << std::put_time(&tm, "[%y/%m/%d %H:%M:%S]");
		std::cout << time.str() << " ";
		switch (logLevel)
		{
		case Level::Debug:
			std::cout << "Debug : ";
			break;
		case Level::Errors:
			std::cout << "Error : ";
			break;
		case Level::Infos:
			std::cout << "Info  : ";
			break;
		}
		std::cout << message << std::endl;
	}
}