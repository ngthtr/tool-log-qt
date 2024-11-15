#include "inc/LogHandler.hpp"
#include <thread>

std::atomic<bool> LogHandler::mIsStopReading = false;

void LogHandler::readLog()
{
    while (!mIsStopReading)
    {
        /* Waiting until good condition*/
        std::unique_lock<std::mutex> lock(mMtx);
        mCv.wait(lock, [this]
                 { return mLogDatabase.empty(); });

        /* Handle reading log and saving to file*/
        FILE *logcat = popen("adb logcat", "r");
        if (logcat == nullptr)
        {
            std::cerr << "Failed to start adb logcat command." << std::endl;
            return;
        }
        char buffer[128];
        if (fgets(buffer, sizeof(buffer), logcat) != nullptr)
        {
            std::cout << buffer;
        }
        fclose(logcat);

        /* Notify other thread*/
        mCv.notify_one();
    }
}

void LogHandler::notifyLog()
{
    while (!mIsStopReading)
    {
        /* Waiting until good condition*/
        std::unique_lock<std::mutex> lock(mMtx);
        mCv.wait(lock, [this]
                 { return !mLogDatabase.empty(); });

        /* Handle notifying new log to controller*/
        Log log = mLogDatabase[0];
        for (auto listener : mLogListeners)
        {
            if (listener)
            {
                listener->notifyLog(log);
            }
        }

        /* Wake up other thread*/
        mCv.notify_one();
    }
}

void LogHandler::startReadLog()
{
    mIsStopReading = false;

    std::thread th_readAdbLog(readLog);
    th_readAdbLog.detach();

    std::thread th_notifyLog(notifyLog);
    th_notifyLog.detach();
}

void LogHandler::stopReadLog()
{
    mIsStopReading = true;
}

void LogHandler::registerLogListener(ILogListener *listener)
{
    if (!listener)
    {
        return;
    }
    mLogListeners.push_back(listener);
}