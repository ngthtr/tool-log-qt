#include "ViewHandler.hpp"
#include <unistd.h>
#include <regex>
#include <iostream>
#include <thread>
int main(int argc, char const *argv[])
{
    ViewHandler *viewHandler;

    viewHandler = new ViewHandler();
    viewHandler->buttonStartClicked();

    sleep(3);
    viewHandler->buttonStopClicked();

    sleep(3);
    viewHandler->saveFileClicked();

    std::cout << "ok men" << std::endl;

    return 0;
}
