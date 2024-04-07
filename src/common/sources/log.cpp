#include <stdexcept>
#include <iostream>


#include "log.h"


namespace Log
{
    void Msg(const char* message)
    {
        std::cout << "[MSG]: " << message << std::endl;
    }

    void Error(const char* message)
    {
        std::cerr << "[ERROR]: " << message << std::endl;
        throw std::runtime_error(message);
    }

    void ThrowVkResult(const char* message, VkResult result)
    {
        std::cerr << "[VK ERROR] VkResult: " << result << std::endl;
        throw std::runtime_error(message + result);
    }
}