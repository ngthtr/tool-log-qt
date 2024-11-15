#include <iostream>
#include <mutex>
#include <vector>
#include "ILogListener.hpp"

class LogHandler
{
private:
    static std::atomic<bool> mIsStopReading;
    std::condition_variable mCv;
    std::mutex mMtx;
    std::vector<Log> mLogDatabase;
    std::vector<ILogListener*> mLogListeners;

    void readLog();
    void notifyLog();
public:
    void registerLogListener(ILogListener* listener);
    void startReadLog();
    void stopReadLog();
};

