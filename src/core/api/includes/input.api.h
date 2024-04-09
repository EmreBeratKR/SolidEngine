#pragma once


#include <GLFW/glfw3.h>


#include "key_code.h"
#include "mouse_button.h"


namespace Engine
{
    class InputAPI
    {
    private:
        GLFWwindow* m_Window;
    
    public:
        InputAPI(GLFWwindow* window);

        static bool GetKeyDown(KeyCode keyCode);
        static bool GetKey(KeyCode keyCode);
        static bool GetKeyUp(KeyCode keyCode);

        static bool GetMouseButtonDown(MouseButton keyCode);
        static bool GetMouseButton(MouseButton keyCode);
        static bool GetMouseButtonUp(MouseButton keyCode);
        static int GetMouseX();
        static int GetMouseY();
        static int GetMouseDeltaX();
        static int GetMouseDeltaY();
    };
}