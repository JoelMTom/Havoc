#pragma once

#include <string>

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

		bool log(const LogLevel Level, const char* msg);
		
	public:

		Hlogger(const LogLevel logLevel, const std::string loggerName)
			:m_logLevel(logLevel), m_loggerName(loggerName)
		{

		}

		void setLogLevel(const LogLevel logLevel)
		{
			m_logLevel = logLevel;
		}

		void setLoggerName(const std::string loggerName)
		{
			m_loggerName = loggerName;
		}
		bool logFatal(const char* msg);
		bool logError(const char* msg);
		bool logWarn(const char* msg);
		bool logDebug(const char* msg);
		bool logInfo(const char* msg);
		bool logTrace(const char* msg);


	private:

		std::string m_loggerName;
		LogLevel m_logLevel;
	};
}

