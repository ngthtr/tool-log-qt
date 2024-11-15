#ifndef LOG_H
#define LOG_H
#include <string>

class Log
{
public:
    std::string date = "default";
    std::string time = "default";
    std::string pid = "default";
    std::string tid = "default";
    std::string level = "default";
    std::string tag = "default";
    std::string msg = "default";

    std::string getLogString() const;
};
#endif