#include "cs_window.h"
#include "cs_events.h"

namespace cs
{
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        switch (action)
        {
            case GLFW_PRESS:
            {
                KeyPressedEvent event{static_cast<Input::Keys>(key)};
                event.dispatch();
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event{static_cast<Input::Keys>(key)};
                event.dispatch();
                break;
            }
            default: break;
        }
    }

    void mouse_button_callback(GLFWwindow* window, int key, int action, int mods)
    {
        switch (action)
        {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event{static_cast<Input::MouseButtons>(key)};
                event.dispatch();
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event{static_cast<Input::MouseButtons>(key)};
                event.dispatch();
                break;
            }
            default: break;
        }
    }

    void mouse_moved_callback(GLFWwindow* window, double xPos, double yPos)
    {
        static double s_xPos{0.0f}, s_yPos{0.0f};
        if (xPos != s_xPos || yPos != s_yPos)
        {
            s_xPos = xPos;
            s_yPos = yPos;

            MouseMovedEvent event{xPos, yPos};
            event.dispatch();
        }
    }


    void mouse_scroll_callback(GLFWwindow* window, double xPos, double yPos)
    {
        static double s_xPos{0.0f}, s_yPos{0.0f};
        if (xPos != s_xPos || yPos != s_yPos)
        {
            s_xPos = xPos;
            s_yPos = yPos;

            MouseScrollEvent event{xPos, yPos};
            event.dispatch();
        }
    }
}