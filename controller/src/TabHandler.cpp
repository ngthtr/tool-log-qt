#include "TabHandler.hpp"
#include <iostream>

void TabHandler::addLog(const Log& log)
{
    //TODO: add log to table in tab
    mLogs.push_back(log);
}

std::vector<Log> TabHandler::getLogs()
{
    return mLogs;
}
