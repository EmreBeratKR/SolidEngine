#pragma once


#define GLFW_INCLUDE_VULKAN


#include <GLFW/glfw3.h>
#include <stb_image.h>


#include "vulkan_graphic_engine.h"


namespace Engine::Rendering
{
    class VulkanTexture
    {
    private:
        VkImage image;
        VkDeviceMemory memory;
        VkImageView imageView;
        VkSampler sampler;
        uint32_t mipLevels;

    public:
        static VulkanTexture* Create(const char* path)
        {
            auto texture = new VulkanTexture();
            auto vulkan = VulkanGraphicEngine::ms_Instance;
            auto logicalDevice = vulkan->GetLogicalDevice();

            int texWidth, texHeight, texChannels;
            stbi_uc* pixels = stbi_load(path, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
            VkDeviceSize imageSize = texWidth * texHeight * 4;

            texture->mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;

            if (!pixels) 
            {
                throw std::runtime_error("failed to load texture image!");
            }

            VkBuffer stagingBuffer;
            VkDeviceMemory stagingBufferMemory;

            vulkan->createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

            void* data;
            vkMapMemory(logicalDevice, stagingBufferMemory, 0, imageSize, 0, &data);
            memcpy(data, pixels, static_cast<size_t>(imageSize));
            vkUnmapMemory(logicalDevice, stagingBufferMemory);

            stbi_image_free(pixels);

            createImage(texWidth, texHeight, texture->mipLevels, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, textureImage, textureImageMemory);

            transitionImageLayout(texture->image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, mipLevels);
            vulkan->copyBufferToImage(stagingBuffer, texture->image, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));

            vkDestroyBuffer(logicalDevice, stagingBuffer, nullptr);
            vkFreeMemory(logicalDevice, stagingBufferMemory, nullptr);

            vulkan->generateMipmaps(texture->image, VK_FORMAT_R8G8B8A8_SRGB, texWidth, texHeight, texture->mipLevels);
        }
    };
}