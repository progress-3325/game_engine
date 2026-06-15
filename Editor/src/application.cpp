#include "application.h"
#include "window.h"

void Application::run()
{
    running = true;
    cs::UI::Window win(800, 400, "Hello World!");
    while (!win.ShouldClose())
    {
        win.Update();
    }
}

bool Application::running = false;