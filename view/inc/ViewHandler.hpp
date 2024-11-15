#ifndef VIEW_HANDLER_H
#define VIEW_HANDLER_H
#include "DLog.hpp"
#include "CommonUiHandler.hpp"

class ViewHandler
{
private:
    std::shared_ptr<CommonUiHandler> mCommonUiHandler;

public:
    ViewHandler();
    void buttonStartClicked();
    void buttonStopClicked();
    void loadFileClicked();
    void saveFileClicked();
};
#endif