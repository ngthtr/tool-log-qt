#include "../../util/inc/Log.hpp"
class ILogListener
{
public:
    virtual void notifyLog(Log log) = 0;
};

