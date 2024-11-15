#ifndef D_LOG_H
#define D_LOG_H

#include <string>
class DLog
{
public:
    static void d(const std::string& tag, const std::string& message);
};
#endif