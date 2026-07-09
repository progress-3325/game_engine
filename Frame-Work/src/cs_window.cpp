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

}