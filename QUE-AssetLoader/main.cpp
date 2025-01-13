#include <SFML/Graphics.hpp>

#include "AppWindow.h"

int main()
{
    AppWindow::initialize();
    AppWindow* app = AppWindow::getInstance();
    app->run();
}