#ifndef ILOG_LISTENER_H
#define ILOG_LISTENER_H

#include "Log.hpp"
class ILogListener
{
public:
    virtual void notifyLog(const Log &log) = 0;
};
#endif