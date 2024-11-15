#include "inc/LogHandler.hpp"
class TestLogListener : public ILogListener
{
private:
    
public:
    void notifyLog(Log log) override 
    {
        std::cout << "notifyLog() is called" << std::endl;
    }
};


int main(int argc, char const *argv[])
{
    LogHandler* logHandler = new LogHandler();
    logHandler->registerLogListener(new TestLogListener());
    logHandler->startReadLog();
    return 0;
}
