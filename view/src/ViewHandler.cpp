#include "ViewHandler.hpp"

ViewHandler::ViewHandler()
{
    mCommonUiHandler = CommonUiHandler::getInstance();
}

void ViewHandler::buttonStartClicked()
{
    DLog::d("ViewHandler", "buttonStartClicked() is called");
    mCommonUiHandler->start();
    // TODO: update state button stop
}

void ViewHandler::buttonStopClicked()
{
    DLog::d("ViewHandler", "buttonStopClicked() is called");
    mCommonUiHandler->stop();
    // TODO: update state button start
}

void ViewHandler::loadFileClicked()
{
    DLog::d("ViewHandler", "loadFileClicked() is called");
    std::string path;
    // TODO: handle get path file
    if (!path.empty())
    {
        mCommonUiHandler->load(path);
    }
}

void ViewHandler::saveFileClicked()
{
    DLog::d("ViewHandler", "saveFileClicked() is called");
    std::string path = "output.txt";
    // TODO: handle get path file
    if (!path.empty())
    {
        mCommonUiHandler->save(path);
    }


}
