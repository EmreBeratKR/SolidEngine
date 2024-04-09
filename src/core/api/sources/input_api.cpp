#include "input.api.h"
#include "application.h"


namespace Engine
{
    InputAPI::InputAPI(GLFWwindow* window)
    {
        this->m_Window = window;
    }


    bool InputAPI::GetKeyDown(KeyCode keycode)
    {
        auto intKeyCode = (int) keycode;
        auto previousState = Application::GetKeyPreviousState(intKeyCode);
        auto currentState = Application::GetKeyCurrentState(intKeyCode);

        return currentState == GLFW_PRESS && previousState != GLFW_PRESS;
    }

    bool InputAPI::GetKey(KeyCode keycode)
    {
        auto intKeyCode = (int) keycode;
        auto previousState = Application::GetKeyPreviousState(intKeyCode);
        auto currentState = Application::GetKeyCurrentState(intKeyCode);

        if (currentState == GLFW_REPEAT) return true;

        return currentState == GLFW_PRESS && previousState != GLFW_RELEASE;
    }

    bool InputAPI::GetKeyUp(KeyCode keycode)
    {
        auto intKeyCode = (int) keycode;
        auto previousState = Application::GetKeyPreviousState(intKeyCode);
        auto currentState = Application::GetKeyCurrentState(intKeyCode);

        return currentState == GLFW_RELEASE && previousState != GLFW_RELEASE;
    }
}