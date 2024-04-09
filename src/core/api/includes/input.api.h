#pragma once


#include <GLFW/glfw3.h>


#include "key_code.h"


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

        static int GetMouseX();
        static int GetMouseY();
    };
}