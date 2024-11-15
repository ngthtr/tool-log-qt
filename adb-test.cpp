#include "LogHandler.hpp"
#include <fstream> // For file handling
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <sstream>
#include <thread>

// std::ofstream outFile("output.txt");

class TestLogListener : public ILogListener
{
public:
    void notifyLog(const Log& log) override
    {
        // outFile << log.getLogString() << std::ends;
        // std::cout << log.getLogString() << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    std::shared_ptr<LogHandler> logHandler = LogHandler::getInstance();
    logHandler->registerLogListener(new TestLogListener());
    logHandler->startReadLog();


    return 0;
}
