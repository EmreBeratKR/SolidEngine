#pragma once


#include <vulkan/vulkan.h>


namespace Engine::Rendering
{
    class VulkanTexture
    {
    private:
        int width;
        int height;
        VkDevice device;
        VkImage image;
        VkDeviceMemory memory;
        VkImageView imageView;
        VkSampler sampler;
        uint32_t mipLevels;


    private:
        void CreateImage(const char* path, VkFormat format);
        void GenerateMipmaps(VkFormat format);
        void CreateImageView(VkFormat format, VkImageAspectFlags aspectFlags);
        void CreateSampler();


    public:
        VulkanTexture(const char* path, VkDevice device, VkFormat format, VkImageAspectFlags aspectFlags);
        ~VulkanTexture();

        VkImageView GetImageView() const;
        VkSampler GetSampler() const;

        static VulkanTexture* Create(const char* path);
    };
}