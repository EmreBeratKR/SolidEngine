#pragma once


#define GLFW_INCLUDE_VULKAN


#include <GLFW/glfw3.h>


namespace Log
{
    void Msg(const char* message);
    void Error(const char* message);
    void ThrowVkResult(const char* message, VkResult result);
}