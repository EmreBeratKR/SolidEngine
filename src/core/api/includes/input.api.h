#pragma once


#include <GLFW/glfw3.h>


#include "key_code.h"
#include "mouse_button.h"


namespace Engine
{
    class InputAPI
    {
    public:
        static bool getKeyDown(KeyCode keyCode);
        static bool getKey(KeyCode keyCode);
        static bool getKeyUp(KeyCode keyCode);

        static bool getMouseButtonDown(MouseButton keyCode);
        static bool getMouseButton(MouseButton keyCode);
        static bool getMouseButtonUp(MouseButton keyCode);
        static int getMouseX();
        static int getMouseY();
        static int getMouseDeltaX();
        static int getMouseDeltaY();
        
        static void setCursorNormal();
		static void setCursorLocked();
    };
}