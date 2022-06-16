#pragma once

#include <string>
#include <memory>

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


		bool Fatal(const char* msg);
		bool Error(const char* msg);
		bool Warn(const char* msg);
		bool Debug(const char* msg);
		bool Info(const char* msg);
		bool Trace(const char* msg);


	private:

		std::string m_loggerName;
		LogLevel m_logLevel;

	};
}

