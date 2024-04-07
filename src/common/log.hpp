#pragma once


#define GLFW_INCLUDE_VULKAN


#include <GLFW/glfw3.h>
#include <stdexcept>


namespace Log
{
    void Error(const char* message)
    {
        throw std::runtime_error(message);
    }

    void ThrowVkResult(const char* message, VkResult result)
    {
        throw std::runtime_error(message + result);
    }
}