#ifndef LOG_HANDLER_H
#define LOG_HANDLER_H

#include <iostream>
#include <mutex>
#include <vector>
#include "ILogListener.hpp"
#include <atomic>
#include <condition_variable>
class LogHandler
{
private:
    static std::atomic_bool mIsStopReading;
    static std::shared_ptr<LogHandler> mInstance;

    std::condition_variable mCvReadConvert;
    std::condition_variable mCvConvertNotify;

    std::mutex mMtxReadConvert;
    std::mutex mMtxConvertNotify;

    std::vector<std::string> mLogStr;
    std::vector<Log> mLogObj;

    std::vector<ILogListener *> mLogListeners;

    void readLog();
    void convertLog();
    void notifyLog();

public:
    static std::shared_ptr<LogHandler> getInstance();
    static Log convert(std::string logStr);
    void registerLogListener(ILogListener *listener);
    void startReadLog();
    void stopReadLog();
};

#endif