#include <stb_image.h>
#include <string>
#include <cmath>


#include "application.h"
#include "vulkan_texture.h"
#include "vulkan_graphic_engine.h"
#include "log.h"


namespace Engine::Rendering
{
    void VulkanTexture::CreateImage(const char* path, VkFormat format)
    {
        auto vulkan = VulkanGraphicEngine::GetInstance();

        int texChannels;
        stbi_uc* pixels = stbi_load(path, &width, &height, &texChannels, STBI_rgb_alpha);
        VkDeviceSize imageSize = width * height * 4;

        mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(width, height)))) + 1;

        if (!pixels) 
        {
            Log::Error("failed to load texture image!");
            return;
        }

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;

        vulkan->createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(device, stagingBufferMemory, 0, imageSize, 0, &data);
        memcpy(data, pixels, static_cast<size_t>(imageSize));
        vkUnmapMemory(device, stagingBufferMemory);

        stbi_image_free(pixels);

        vulkan->createImage(width, height, mipLevels, format, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, image, memory);

        vulkan->transitionImageLayout(image, format, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, mipLevels);
        vulkan->copyBufferToImage(stagingBuffer, image, static_cast<uint32_t>(width), static_cast<uint32_t>(height));

        vkDestroyBuffer(device, stagingBuffer, nullptr);
        vkFreeMemory(device, stagingBufferMemory, nullptr);
    }

    void VulkanTexture::GenerateMipmaps(VkFormat format)
    {
        auto vulkan = VulkanGraphicEngine::GetInstance();

        vulkan->generateMipmaps(image, format, width, height, mipLevels);
    }

    void VulkanTexture::CreateImageView(VkFormat format, VkImageAspectFlags aspectFlags)
    {
        VkImageViewCreateInfo viewInfo{};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = image;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = format;
        viewInfo.subresourceRange.aspectMask = aspectFlags;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = mipLevels;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = 1;

        auto result = vkCreateImageView(device, &viewInfo, nullptr, &imageView);

        if (result != VK_SUCCESS)
        {
            Log::ThrowVkResult("failed to create texture image view!", result);
        }
    }

    void VulkanTexture::CreateSampler()
    {
        auto vulkan = VulkanGraphicEngine::GetInstance();
        auto physicalDevice = vulkan->GetPhysicalDevice();
        auto logicalDevice = vulkan->GetLogicalDevice();

        VkPhysicalDeviceProperties properties{};
        vkGetPhysicalDeviceProperties(physicalDevice, &properties);

        VkSamplerCreateInfo samplerInfo{};
        samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerInfo.magFilter = VK_FILTER_LINEAR;
        samplerInfo.minFilter = VK_FILTER_LINEAR;
        samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.anisotropyEnable = VK_TRUE;
        samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
        samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        samplerInfo.unnormalizedCoordinates = VK_FALSE;
        samplerInfo.compareEnable = VK_FALSE;
        samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
        samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        samplerInfo.mipLodBias = 0.0f;
        samplerInfo.minLod = 0.0f;
        samplerInfo.maxLod = 0.0f;

        auto result = vkCreateSampler(logicalDevice, &samplerInfo, nullptr, &sampler);

        if (result != VK_SUCCESS) 
        {
            Log::ThrowVkResult("failed to create texture sampler!", result);
        }
    }


    VulkanTexture::VulkanTexture(const char* path, VkDevice device, VkFormat format, VkImageAspectFlags aspectFlags) : device{device}
    {
        CreateImage(path, format);
        GenerateMipmaps(format);
        CreateImageView(format, aspectFlags);
        CreateSampler();
    }

    VulkanTexture::~VulkanTexture()
    {
        vkDestroySampler(device, sampler, nullptr);
        vkDestroyImageView(device, imageView, nullptr);

        vkDestroyImage(device, image, nullptr);
        vkFreeMemory(device, memory, nullptr);
    }


    VkImageView VulkanTexture::GetImageView() const
    {
        return imageView;
    }

    VkSampler VulkanTexture::GetSampler() const
    {
        return sampler;
    }
}