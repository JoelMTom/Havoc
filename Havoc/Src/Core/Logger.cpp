#include "Logger.h"

#include <string>

#include "fmt/format.h"
#include "fmt/color.h"

namespace Havoc
{
	bool Hlogger::log(const LogLevel Level, const char* msg)
	{
		const char* levels[] = {"Fatal", "Error", "Debug", "Warn", "Info", "Trace"};
		std::string format = "{0}: {1}: {2}\n";
		if (Level == LogLevel::Fatal && Level <= m_logLevel)
			fmt::print(fg(fmt::color::white) | bg(fmt::color::crimson) | fmt::emphasis::bold, "{0}: {1}: {2}\n", levels[static_cast<int>(LogLevel::Fatal)], m_loggerName, msg);
		else if (Level == LogLevel::Error && Level <= m_logLevel)
			fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "{0}: {1}: {2}\n", levels[static_cast<int>(LogLevel::Error)], m_loggerName, msg);
		else if (Level == LogLevel::Warn && Level <= m_logLevel)
			fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold, "{0}: {1}: {2}\n", levels[static_cast<int>(LogLevel::Warn)], m_loggerName, msg);
		else if (Level == LogLevel::Debug && Level <= m_logLevel)
			fmt::print(fg(fmt::color::blue) | fmt::emphasis::bold, "{0}: {1}: {2}\n", levels[static_cast<int>(LogLevel::Debug)], m_loggerName, msg);
		else if (Level == LogLevel::Info && Level <= m_logLevel)
			fmt::print(fg(fmt::color::white) | fmt::emphasis::bold, "{0}: {1}: {2}\n", levels[static_cast<int>(LogLevel::Info)], m_loggerName, msg);
		else if (Level == LogLevel::Trace && Level <= m_logLevel)
			fmt::print(fg(fmt::color::gray) | fmt::emphasis::bold, "{0}: {1}: {2}\n", levels[static_cast<int>(LogLevel::Trace)], m_loggerName, msg);
		return true;
	}

	bool Hlogger::logFatal(const char* msg)
	{
		if (log(LogLevel::Fatal, msg))
			return true;
		return false;
	}

	bool Hlogger::logError(const char* msg)
	{
		if (log(LogLevel::Error, msg))
			return true;
		return false;
	}

	bool Hlogger::logWarn(const char* msg)
	{
		if (log(LogLevel::Warn, msg))
			return true;
		return false;
	}

	bool Hlogger::logDebug(const char* msg)
	{
		if (log(LogLevel::Debug, msg))
			return true;
		return false;
	}

	bool Hlogger::logInfo(const char* msg)
	{
		if (log(LogLevel::Info, msg))
			return true;
		return false;
	}

	bool Hlogger::logTrace(const char* msg)
	{
		if (log(LogLevel::Trace, msg))
			return true;
		return false;
	}
}


