#include "application.h"
#include "logging.h"
#include "window.h"
#include <GLFW/glfw3.h>

void Application::run()
{
    running = true;
    cs::UI::Window win(800, 400, "Hello World!");
    while (!win.ShouldClose())
    {
        win.Update();
    }
    glfwTerminate();
    cspace::logger::log("Closed!", cspace::L_CODE::C_INFO);
}

bool Application::running = false;