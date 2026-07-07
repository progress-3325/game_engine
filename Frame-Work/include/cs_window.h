#pragma once
#include <GLFW/glfw3.h>
#include "core.h"

namespace cs
{
    class Window
    {
    public:
        Window() = default;
        Window(const uint32_t& p_width, const uint32_t& p_height, cstring p_title)
            : width(p_width), height(p_height), title(p_title) 
        {
            glfwInit();
            this->window = glfwCreateWindow(this->width, this->height, this->title, nullptr, nullptr);

            glfwMakeContextCurrent(this->window);
            glfwSetWindowUserPointer(this->window, this);
        }

        void pollEvents() const { glfwPollEvents(); }
        void swapBuffers() const { glfwSwapBuffers(this->window); }

        operator GLFWwindow*()
        {
            return this->window;
        }
    private:
        GLFWwindow* window = nullptr;
        uint32_t width{0}, height{0};
        cstring title{'\0'};
    };

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
}