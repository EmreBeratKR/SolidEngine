#pragma once


#define GLFW_INCLUDE_VULKAN


#include <GLFW/glfw3.h>


namespace Engine::Rendering
{
    class VulkanTexture
    {
        public:
            VulkanTexture(const char* path, VkDevice device, VkFormat format, VkImageAspectFlags aspectFlags);

            VkImageView GetImageView() const;
            VkSampler GetSampler() const;
    };
}