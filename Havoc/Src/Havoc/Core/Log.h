#pragma once

#include <memory>

#include "Logger.h"


namespace Havoc
{
	class Log
	{
	public:

		static void Init();

		inline static std::shared_ptr<Hlogger>& GetCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<Hlogger>& GetClientLogger() { return s_clientLogger; }

	private:
		static std::shared_ptr<Hlogger> s_coreLogger;
		static std::shared_ptr<Hlogger> s_clientLogger;
	};
}


#define H_CORE_FATAL(...) ::Havoc::Log::GetCoreLogger()->Fatal(__VA_ARGS__)
#define H_CORE_ERROR(...) ::Havoc::Log::GetCoreLogger()->Error(__VA_ARGS__)
#define H_CORE_WARN(...) ::Havoc::Log::GetCoreLogger()->Warn(__VA_ARGS__)
#define H_CORE_DEBUG(...) ::Havoc::Log::GetCoreLogger()->Debug(__VA_ARGS__)
#define H_CORE_INFO(...) ::Havoc::Log::GetCoreLogger()->Info(__VA_ARGS__)
#define H_CORE_TRACE(...) ::Havoc::Log::GetCoreLogger()->Trace(__VA_ARGS__)

#define H_CLIENT_FATAL(...) ::Havoc::Log::GetClientLogger()->Fatal(__VA_ARGS__)
#define H_CLIENT_ERROR(...) ::Havoc::Log::GetClientLogger()->Error(__VA_ARGS__)
#define H_CLIENT_WARN(...) ::Havoc::Log::GetClientLogger()->Warn(__VA_ARGS__)
#define H_CLIENT_DEBUG(...) ::Havoc::Log::GetClientLogger()->Debug(__VA_ARGS__)
#define H_CLIENT_INFO(...) ::Havoc::Log::GetClientLogger()->Info(__VA_ARGS__)
#define H_CLIENT_TRACE(...) ::Havoc::Log::GetClientLogger()->Trace(__VA_ARGS__)