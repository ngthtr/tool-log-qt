#include "DLog.hpp"
#include <iostream>

void DLog::d(const std::string& tag, const std::string& message)
{
    std::cout << tag << " : " << message << std::endl;
}