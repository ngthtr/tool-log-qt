#include <string>
class Log
{
public:
    std::string date;
    std::string time;
    std::string tag;
    std::string msg;

    std::string getLogString();
};

