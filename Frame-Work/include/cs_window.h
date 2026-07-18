#pragma once
#include <GLFW/glfw3.h>
#include "core.h"
#include "cs_logging.h"

namespace cs
{
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    void mouse_button_callback(GLFWwindow* window, int key, int action, int mods);

    void mouse_moved_callback(GLFWwindow* window, double xPos, double yPos);

    void mouse_scroll_callback(GLFWwindow* window, double xPos, double yPos);

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    void window_close_callback(GLFWwindow* window);

    void char_input_callback(GLFWwindow* window, unsigned int codepoint);

    void cursor_enter_callback(GLFWwindow* window, int entered);

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
            this->mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

            glfwMakeContextCurrent(this->window);
            glfwSetWindowUserPointer(this->window, this);
            glfwSetKeyCallback(this->window, key_callback);
            glfwSetMouseButtonCallback(this->window, mouse_button_callback);
            glfwSetCursorPosCallback(this->window, mouse_moved_callback);
            glfwSetScrollCallback(this->window, mouse_scroll_callback);
            /*
            glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
            glfwSetWindowCloseCallback(this->window, window_close_callback);
            glfwSetCharCallback(this->window, char_input_callback);
            glfwSetCursorEnterCallback(this->window, cursor_enter_callback);
            */
        }

        void pollEvents() const { glfwPollEvents(); }
        void swapBuffers() const { glfwSwapBuffers(this->window); }
        bool shouldClose() const { return glfwWindowShouldClose(this->window); }

        GLFWwindow* nativeHandle() const { return this->window; }

        ~Window()
        {
            if (this->window)
                glfwDestroyWindow(this->window);
        }
    private:
        GLFWwindow* window = nullptr;
        const GLFWvidmode* mode = nullptr;
        uint32_t width{0}, height{0};
        cstring title{""};
    };
}