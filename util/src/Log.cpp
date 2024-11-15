#include "Log.hpp"

std::string Log::getLogString() const
{
    std::string logStr = date + " " + time + " " + pid + " " + tid + " " + level + " " + tag + " : " + msg;
    return logStr;
}