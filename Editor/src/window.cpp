#include "window.h"
#include <GLFW/glfw3.h>
#include "logging.h"

namespace cs
{
    namespace UI
    {
        Window::~Window() {};
        Window::Window(int width, int height, const char* title)
        {
            if (!glfwInit())
                cspace::logger::log("GLFW wasn't initialized properly", cspace::L_CODE::C_ERROR);

            this->m_window = glfwCreateWindow(width, height, title, NULL, NULL);

            if (!m_window)
            {
                glfwTerminate();
                cspace::logger::log("Window wasn't initialized properly", cspace::L_CODE::C_ERROR);
            }

            glfwMakeContextCurrent(this->m_window);

            this->running = true;
        }

        void Window::Update()
        {
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(this->m_window);
            
            glfwPollEvents();

            this->running = !glfwWindowShouldClose(this->m_window);
        }

        void Window::SetShouldClose(bool value)
        {
            this->running = !value;
        }

        bool Window::ShouldClose() const {return !this->running;}
}
}