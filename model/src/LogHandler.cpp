#include "LogHandler.hpp"
#include "DLog.hpp"
#include <thread>
#include <regex>

std::atomic_bool LogHandler::mIsStopReading = false;
std::shared_ptr<LogHandler> LogHandler::mInstance = nullptr;

std::shared_ptr<LogHandler> LogHandler::getInstance()
{
    mInstance = mInstance == NULL ? std::make_shared<LogHandler>() : mInstance;
    return mInstance;
}

Log LogHandler::convert(std::string logStr)
{
    logStr.pop_back(); // Remove character end of line - '\n'
    std::regex logcatPattern(R"((\d{2}-\d{2}) (\d{2}:\d{2}:\d{2}\.\d{3})\s+(\d+)\s+(\d+)\s+([VDIWEF])\s+([\w/[\]0-9]+): (.+))");
    std::smatch matches;
    Log logObj;
    try
    {
        if (std::regex_match(logStr, matches, logcatPattern))
        {
            logObj.date = matches[1];
            logObj.time = matches[2];
            logObj.pid = matches[3];
            logObj.tid = matches[4];
            logObj.level = matches[5];
            logObj.tag = matches[6];
            logObj.msg = matches[7];
            return logObj;
        }
        else
        {
            // DLog::d("LogHandler", "convert(): log-line is not matched");
            // std::cout << logStr << std::endl;
        }
    }
    catch (const std::regex_error &e)
    {
        std::cerr << "Regex error: " << e.what() << std::endl;
    }
    return logObj;
}

void LogHandler::readLog()
{
    FILE *logcat = popen("adb logcat", "r");
    if (logcat == nullptr)
    {
        return;
    }
    char buffer[1280];

    while (!mIsStopReading)
    {
        /* Waiting until good condition*/
        std::unique_lock<std::mutex> lockReadConvert(mMtxReadConvert);
        mCvReadConvert.wait(lockReadConvert, [this]
                            { return mLogStr.empty(); });

        /* Handle reading log and saving to file*/
        if (fgets(buffer, sizeof(buffer), logcat) != nullptr)
        {
            mLogStr.push_back(buffer);
            std::cout << buffer << std::endl;
        }

        /* Notify other thread*/
        mCvReadConvert.notify_one();
    }

    fclose(logcat);
}

void LogHandler::convertLog()
{
    while (!mIsStopReading)
    {
        /* Waiting util good condition*/
        std::unique_lock<std::mutex> lockReadConvert(mMtxReadConvert);
        std::unique_lock<std::mutex> lockConvertNotify(mMtxConvertNotify);

        mCvReadConvert.wait(lockReadConvert, [this]
                            { return !mLogStr.empty(); });
        mCvConvertNotify.wait(lockConvertNotify, [this]
                              { return mLogObj.empty(); });

        /* Handle convert log string to object*/
        Log logObj = convert(mLogStr[0]);
        mLogStr.pop_back();
        mLogObj.push_back(logObj);

        /* Notify other thread*/
        mCvReadConvert.notify_one();
        mCvConvertNotify.notify_one();
    }
}

void LogHandler::notifyLog()
{
    while (!mIsStopReading)
    {
        /* Waiting until good condition*/
        std::unique_lock<std::mutex> lockConvertNotify(mMtxConvertNotify);
        mCvConvertNotify.wait(lockConvertNotify, [this]
                              { return !mLogObj.empty(); });

        /* Handle notifying new log to controller*/
        Log logObj = mLogObj[0];
        mLogObj.pop_back();
        for (auto listener : mLogListeners)
        {
            if (listener)
            {
                listener->notifyLog(logObj);
            }
        }

        /* Wake up other thread*/
        mCvConvertNotify.notify_one();
    }
}

void LogHandler::startReadLog()
{
    DLog::d("LogHandler", "startReadLog is called");

    mIsStopReading = false;
    std::thread th_startReadLog([this] () {
        std::thread th_readLog(&LogHandler::readLog, this);
        std::thread th_convertLog(&LogHandler::convertLog, this);
        std::thread th_notifyLog(&LogHandler::notifyLog, this);

        th_readLog.join();
        th_convertLog.join();
        th_notifyLog.join();
    });

    th_startReadLog.detach();
}

void LogHandler::stopReadLog()
{
    DLog::d("LogHandler", "stopReadLog is called");
    mIsStopReading = true;
}

void LogHandler::registerLogListener(ILogListener *listener)
{
    if (!listener)
    {
        return;
    }
    DLog::d("LogHandler", "registerLogListener is called");
    mLogListeners.push_back(listener);
}