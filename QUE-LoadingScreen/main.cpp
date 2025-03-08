#include <SFML/Graphics.hpp>

#include "Window/AppWindow.h"

extern "C"
{
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
    __declspec(dllexport) unsigned int NvOptimusEnablement = 0x00000001;
}

int main()
{
    AppWindow::initialize();
    AppWindow* app = AppWindow::getInstance();
    app->run();
}