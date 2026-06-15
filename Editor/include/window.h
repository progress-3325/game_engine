#pragma once
#include <GLFW/glfw3.h>

namespace cs
{
    namespace UI
    {    class Window
        {
        public:
            Window() = default;
            Window(int width, int height, const char* title);
            ~Window();

            void Update();
            bool ShouldClose() const;
            void SetShouldClose(bool value);

            GLFWwindow* GetGLFWwindow() const;
        private:
            GLFWwindow* m_window;
            bool running = false;
        };
    }
}