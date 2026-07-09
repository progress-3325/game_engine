#pragma once
#include <GLFW/glfw3.h>
#include "core.h"
#include "cs_logging.h"

namespace cs
{
    class Window
    {
    public:
        Window() = default;
        Window(const uint32_t& p_width, const uint32_t& p_height, cstring p_title)
            : width(p_width), height(p_height), title(p_title) 
        {
            if (!glfwInit()) logger::log("Failed to initialize GLFW!", L_CODE::C_ERROR);
            this->window = glfwCreateWindow(this->width, this->height, this->title, nullptr, nullptr);
            if (!window)
            {
                glfwTerminate();
                logger::log("Failed to create GLFW window!", L_CODE::C_ERROR);
            }

            glfwMakeContextCurrent(this->window);
            glfwSetWindowUserPointer(this->window, this);
            glfwSetKeyCallback(this->window, key_callback);
            glfwSetMouseButtonCallback(this->window, mouse_button_callback);
        }

        void pollEvents() const { glfwPollEvents(); }
        void swapBuffers() const { glfwSwapBuffers(this->window); }
        bool shouldClose() const { return glfwWindowShouldClose(this->window); }

        GLFWwindow* nativeHandle() const { return this->window; }

        ~Window()
        {
            if (this->window)
                glfwDestroyWindow(this->window);
            glfwTerminate();
        }
    private:
        GLFWwindow* window = nullptr;
        uint32_t width{0}, height{0};
        cstring title{'\0'};
    };

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    void mouse_button_callback(GLFWwindow* window, int key, int action, int mods);
}