#pragma once


#include <vulkan/vulkan.h>


namespace Log
{
    void Msg(const char* message);
    void Error(const char* message);
    void ThrowVkResult(const char* message, VkResult result);
}