
#ifndef COMPONENT_HANDLER_H
#define COMPONENT_HANDLER_H

#include <string>
#include "TableHandler.hpp"
#include "LogHandler.hpp"

class CommonUiHandler
{
private:
    static std::shared_ptr<CommonUiHandler> mInstance;
    std::shared_ptr<TableHandler> mTableHandler;
    std::shared_ptr<LogHandler> mLogHandler;

    class LogListener : public ILogListener
    {
    private:
        std::shared_ptr<TableHandler> mTableHandler;
    public:
        LogListener(std::shared_ptr<TableHandler> _tableHandler);
        void notifyLog(const Log &log) override;
    };

public:
    CommonUiHandler();

    static std::shared_ptr<CommonUiHandler> getInstance();

    void start();
    void stop();
    void load(std::string path);
    void save(std::string path);
};

#endif