#include "CommonUiHandler.hpp"
#include <fstream>
#include <thread>

std::shared_ptr<CommonUiHandler> CommonUiHandler::mInstance = nullptr;

void CommonUiHandler::LogListener::notifyLog(const Log &log)
{
    mTableHandler->currentTab->addLog(log);
}

CommonUiHandler::LogListener::LogListener(std::shared_ptr<TableHandler> _tableHandler)
{
    mTableHandler = _tableHandler;
}

CommonUiHandler::CommonUiHandler()
{
    mTableHandler = TableHandler::getInstance();
    mLogHandler = LogHandler::getInstance();
    mLogHandler->registerLogListener(new LogListener(mTableHandler));
}
std::shared_ptr<CommonUiHandler> CommonUiHandler::getInstance()
{
    mInstance = mInstance == nullptr ? std::make_shared<CommonUiHandler>() : mInstance;
    return mInstance;
}

void CommonUiHandler::start()
{
    mLogHandler->stopReadLog();
    mLogHandler->startReadLog();
}

void CommonUiHandler::stop()
{
    mLogHandler->stopReadLog();
}

void CommonUiHandler::load(std::string path)
{
    std::ifstream infile(path);
    if (!infile.is_open())
    {
        return;
    }
    
    std::string line;
    std::thread th_readLogFromFile([&infile, &line, this]() {
        while (getline(infile, line)) {
            Log log = LogHandler::convert(line);
            this->mTableHandler->currentTab->addLog(log);
        } 
    });
    th_readLogFromFile.detach();
}

void CommonUiHandler::save(std::string path)
{
    std::ofstream outfile(path);
    if (!outfile.is_open())
    {
        return;
    }
    std::vector<Log> mLogs = mTableHandler->currentTab->getLogs();
    for (Log log : mLogs)
    {
        outfile << log.getLogString() << std::endl;
    }
    outfile.close();
}
