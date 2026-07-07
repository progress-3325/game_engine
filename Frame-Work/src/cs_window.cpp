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
                (new KeyPressedEvent(static_cast<Input::Keys>(key)))->dispatch();
                break;
            }
            case GLFW_RELEASE:
            {
                (new KeyReleasedEvent(static_cast<Input::Keys>(key)))->dispatch();
                break;
            }
            default: break;
        }
    }
}