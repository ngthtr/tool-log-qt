#ifndef TAB_HANDLER_H
#define TAB_HANDLER_H
#include "StateUiStorage.hpp"
#include "Log.hpp"
#include <vector>

class TabHandler
{
private:
    std::vector<Log> mLogs;
public:
    void addLog(const Log& log);
    std::vector<Log> getLogs();
};

#endif