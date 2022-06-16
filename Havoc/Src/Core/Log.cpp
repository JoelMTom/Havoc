#include "Log.h"


namespace Havoc
{
	std::shared_ptr<Hlogger> Log::s_coreLogger;
	std::shared_ptr<Hlogger> Log::s_clientLogger;

	void Log::Init()
	{
		s_coreLogger =  std::make_shared<Hlogger>(Hlogger(LogLevel::Trace, "Havoc"));
		s_clientLogger =  std::make_shared<Hlogger>(Hlogger(LogLevel::Trace, "HavocLand"));
	}
}