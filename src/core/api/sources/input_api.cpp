#include "input.api.h"
#include "application.h"


namespace Engine
{
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


    bool InputAPI::getKeyDown(KeyCode keycode)
    {
        auto intKeyCode = (int) keycode;
        auto previousState = Application::getKeyPreviousState(intKeyCode);
        auto currentState = Application::getKeyCurrentState(intKeyCode);

        return IsDown(previousState, currentState);
    }

    bool InputAPI::getKey(KeyCode keycode)
    {
        auto intKeyCode = (int) keycode;
        auto previousState = Application::getKeyPreviousState(intKeyCode);
        auto currentState = Application::getKeyCurrentState(intKeyCode);

        return IsHold(previousState, currentState);
    }

    bool InputAPI::getKeyUp(KeyCode keycode)
    {
        auto intKeyCode = (int) keycode;
        auto previousState = Application::getKeyPreviousState(intKeyCode);
        auto currentState = Application::getKeyCurrentState(intKeyCode);
        
        return IsUp(previousState, currentState);
    }


    bool InputAPI::getMouseButtonDown(MouseButton mouseButton)
    {
        auto intMouseButton = (int) mouseButton;
        auto previousState = Application::getMouseButtonPreviousState(intMouseButton);
        auto currentState = Application::getMouseButtonCurrentState(intMouseButton);

        return IsDown(previousState, currentState);
    }

    bool InputAPI::getMouseButton(MouseButton mouseButton)
    {
        auto intMouseButton = (int) mouseButton;
        auto previousState = Application::getMouseButtonPreviousState(intMouseButton);
        auto currentState = Application::getMouseButtonCurrentState(intMouseButton);

        return IsHold(previousState, currentState);
    }

    bool InputAPI::getMouseButtonUp(MouseButton mouseButton)
    {
        auto intMouseButton = (int) mouseButton;
        auto previousState = Application::getMouseButtonPreviousState(intMouseButton);
        auto currentState = Application::getMouseButtonCurrentState(intMouseButton);

        return IsUp(previousState, currentState);
    }

    int InputAPI::getMouseX()
    {
        return Application::getMouseX();
    }

    int InputAPI::getMouseY()
    {
        return Application::getMouseY();
    }

    int InputAPI::getMouseDeltaX()
    {
        return Application::getMouseDeltaX();
    }

    int InputAPI::getMouseDeltaY()
    {
        return Application::getMouseDeltaY();
    }
}