#include "input.api.h"
#include "application.h"


namespace Engine
{
    InputAPI::InputAPI(GLFWwindow* window)
    {
        this->m_Window = window;
    }


    static bool IsDown(int previousState, int currentState)
    {
        return currentState == GLFW_PRESS && previousState != GLFW_PRESS;
    }

    static bool IsHold(int previousState, int currentState)
    {
        if (currentState == GLFW_REPEAT) return true;

        return currentState == GLFW_PRESS && previousState != GLFW_RELEASE;
    }

    static bool IsUp(int previousState, int currentState)
    {
        return currentState == GLFW_RELEASE && previousState != GLFW_RELEASE;
    }


    bool InputAPI::GetKeyDown(KeyCode keycode)
    {
        auto intKeyCode = (int) keycode;
        auto previousState = Application::GetKeyPreviousState(intKeyCode);
        auto currentState = Application::GetKeyCurrentState(intKeyCode);

        return IsDown(previousState, currentState);
    }

    bool InputAPI::GetKey(KeyCode keycode)
    {
        auto intKeyCode = (int) keycode;
        auto previousState = Application::GetKeyPreviousState(intKeyCode);
        auto currentState = Application::GetKeyCurrentState(intKeyCode);

        return IsHold(previousState, currentState);
    }

    bool InputAPI::GetKeyUp(KeyCode keycode)
    {
        auto intKeyCode = (int) keycode;
        auto previousState = Application::GetKeyPreviousState(intKeyCode);
        auto currentState = Application::GetKeyCurrentState(intKeyCode);

        return IsUp(previousState, currentState);
    }


    bool InputAPI::GetMouseButtonDown(MouseButton mouseButton)
    {
        auto intMouseButton = (int) mouseButton;
        auto previousState = Application::GetMouseButtonPreviousState(intMouseButton);
        auto currentState = Application::GetMouseButtonCurrentState(intMouseButton);

        return IsDown(previousState, currentState);
    }

    bool InputAPI::GetMouseButton(MouseButton mouseButton)
    {
        auto intMouseButton = (int) mouseButton;
        auto previousState = Application::GetMouseButtonPreviousState(intMouseButton);
        auto currentState = Application::GetMouseButtonCurrentState(intMouseButton);

        return IsHold(previousState, currentState);
    }

    bool InputAPI::GetMouseButtonUp(MouseButton mouseButton)
    {
        auto intMouseButton = (int) mouseButton;
        auto previousState = Application::GetMouseButtonPreviousState(intMouseButton);
        auto currentState = Application::GetMouseButtonCurrentState(intMouseButton);

        return IsUp(previousState, currentState);
    }

    int InputAPI::GetMouseX()
    {
        return Application::GetMouseX();
    }

    int InputAPI::GetMouseY()
    {
        return Application::GetMouseY();
    }

    int InputAPI::GetMouseDeltaX()
    {
        return Application::GetMouseDeltaX();
    }

    int InputAPI::GetMouseDeltaY()
    {
        return Application::GetMouseDeltaY();
    }
}