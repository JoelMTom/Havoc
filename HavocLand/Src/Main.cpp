#include "Core/Core.h"
#include "Core/Logger.h"

int main()
{
    Havoc::Hlogger log(Havoc::LogLevel::Info, "HavocLogger");
    log.logFatal("Havoc Engine");
    log.logError("Havoc Engine");
    log.logWarn("Havoc Engine");
    log.logDebug("Havoc Engine");
    log.logInfo("Havoc Engine");
    log.logTrace("Havoc Engine");
    return 0;
}