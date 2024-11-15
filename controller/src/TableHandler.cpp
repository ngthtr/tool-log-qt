#include "TableHandler.hpp"
#include "LogHandler.hpp"

std::shared_ptr<TableHandler> TableHandler::mInstance = nullptr;

TableHandler::TableHandler()
{
    currentTab = new TabHandler();
}

std::shared_ptr<TableHandler> TableHandler::getInstance()
{
    mInstance = mInstance == nullptr ? std::make_shared<TableHandler>() : mInstance;
    return mInstance;
}
