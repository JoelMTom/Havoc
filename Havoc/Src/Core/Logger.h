#pragma once

#include "fmt/format.h"
#include "fmt/color.h"


namespace Havoc
{
	enum class LogLevel
	{
		Fatal = 0,
		Error,
		Warn,
		Debug,
		Info,
		Trace
	};

	class Hlogger
	{
		template<typename... Args>
		void log(const LogLevel Level, Args&& ... args)
		{
			const char* levels[] = { "Fatal", "Error", "Warn", "Debug", "Info", "Trace" };
			const char* format = "{0}: {1}: {2}\n";
			if (Level == LogLevel::Fatal && Level <= m_logLevel)
				fmt::print(fg(fmt::color::white) | bg(fmt::color::crimson) | fmt::emphasis::bold, format, levels[static_cast<int>(LogLevel::Fatal)], m_loggerName, fmt::format(std::forward<Args>(args)...));
			else if (Level == LogLevel::Error && Level <= m_logLevel)
				fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, format, levels[static_cast<int>(LogLevel::Error)], m_loggerName, fmt::format(std::forward<Args>(args)...));
			else if (Level == LogLevel::Warn && Level <= m_logLevel)
				fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold, format, levels[static_cast<int>(LogLevel::Warn)], m_loggerName, fmt::format(std::forward<Args>(args)...));
			else if (Level == LogLevel::Debug && Level <= m_logLevel)
				fmt::print(fg(fmt::color::blue) | fmt::emphasis::bold, format, levels[static_cast<int>(LogLevel::Debug)], m_loggerName, fmt::format(std::forward<Args>(args)...));
			else if (Level == LogLevel::Info && Level <= m_logLevel)
				fmt::print(fg(fmt::color::white) | fmt::emphasis::bold, format, levels[static_cast<int>(LogLevel::Info)], m_loggerName, fmt::format(std::forward<Args>(args)...));
			else if (Level == LogLevel::Trace && Level <= m_logLevel)
				fmt::print(fg(fmt::color::gray) | fmt::emphasis::bold, format, levels[static_cast<int>(LogLevel::Trace)], m_loggerName, fmt::format(std::forward<Args>(args)...));
		}
		
	public:

		Hlogger()
		{
			m_loggerName = "HavocLogger";
			m_logLevel = LogLevel::Trace;
		}

		Hlogger(const LogLevel logLevel, const char* loggerName)
			:m_logLevel(logLevel), m_loggerName(loggerName)
		{

		}


		Hlogger(const char* loggerName)
			:m_loggerName(loggerName)
		{
			m_logLevel = LogLevel::Trace;
		}

		void setLogLevel(const LogLevel logLevel)
		{
			m_logLevel = logLevel;
		}

		void setLoggerName(const char* loggerName)
		{
			m_loggerName = loggerName;
		}

		template<typename... Args>
		void Fatal(Args&& ... args)
		{
			log(LogLevel::Fatal, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void Error(Args&& ... args)
		{
			log(LogLevel::Error, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void Warn(Args&& ... args)
		{
			log(LogLevel::Warn, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void Debug(Args&& ... args)
		{
			log(LogLevel::Debug, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void Info(Args&& ... args)
		{
			log(LogLevel::Info, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void Trace(Args&& ... args)
		{
			log(LogLevel::Trace, std::forward<Args>(args)...);
		}


	private:

		const char* m_loggerName;
		LogLevel m_logLevel;

	};
}

