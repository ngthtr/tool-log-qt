#include "inc/Log.hpp"

std::string Log::getLogString()
{
    return date + " " + time + " " + tag + " " + msg;
}