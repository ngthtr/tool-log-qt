#ifndef TABLE_HANDLER_H
#define TABLE_HANDLER_H
#include "StateUiStorage.hpp"
#include "TabHandler.hpp"
#include <vector>
#include <memory>

class TableHandler
{
private:
    static std::shared_ptr<TableHandler> mInstance;

public:
    TableHandler();
    static std::shared_ptr<TableHandler> getInstance();    
    TabHandler *currentTab;
};
#endif