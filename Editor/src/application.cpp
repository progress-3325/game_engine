#include "application.h"
#include "cs_logging.h"
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
    cs::logger::log("Closed!", cs::L_CODE::C_INFO);
}

bool Application::running = false;