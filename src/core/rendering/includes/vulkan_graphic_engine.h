#pragma once


#define GLFW_INCLUDE_VULKAN


#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <optional>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <set>


#include "fwd.h"


namespace Engine::Rendering
{
	class VulkanGraphicEngine
	{
        const int MAX_FRAMES_IN_FLIGHT = 2;

        const std::vector<const char*> validationLayers =
        {
            "VK_LAYER_KHRONOS_validation"
        };

        const std::vector<const char*> deviceExtensions =
        {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        struct QueueFamilyIndices
        {
            std::optional<uint32_t> graphicsFamily;
            std::optional<uint32_t> presentFamily;

            bool isComplete()
            {
                return graphicsFamily.has_value() && presentFamily.has_value();
            }
        };

        struct SwapChainSupportDetails
        {
            VkSurfaceCapabilitiesKHR capabilities;
            std::vector<VkSurfaceFormatKHR> formats;
            std::vector<VkPresentModeKHR> presentModes;
        };

    private:
        static VulkanGraphicEngine* ms_Instance;

        Application* engineWindow;
        GLFWwindow* window;

        VkInstance instance;
        VkSurfaceKHR surface;

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice logicalDevice;

        VkQueue graphicsQueue;
        VkQueue presentQueue;

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;

        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;

        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;

        VertexBuffer* vertexBuffer;
        IndexBuffer* indexBuffer;

        VulkanDescriptorSetLayout* descriptorSetLayout;
        VulkanDescriptorPool* descriptorPool;
        std::vector<VulkanDescriptorWriter*> descriptorWriters;
        std::vector<VkDescriptorSet> descriptorSets;

        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;
        std::vector<void*> uniformBuffersMapped;

        VulkanTexture* texture;

        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        VkImageView depthImageView;

        uint32_t currentFrame = 0;
        uint32_t currentImageIndex = 0;

    private:
        void init(Application* engineWindow);
        void cleanup();
        void createInstance();
        void createSurface();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createSwapChain();
        void createImageViews();
        void createRenderPass();
        void createGraphicsPipeline();
        void createFramebuffers();
        void createCommandPool();
        void createCommandBuffer();
        void createSyncObjects();
        void recreateSwapChain();
        void cleanupSwapChain();
        void createDescriptorSetLayout();
        void createUniformBuffers();
        void createDescriptorPool();
        void createDescriptorSets();
        void createTextureImage();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);
        void createDepthResources();
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        VkFormat findDepthFormat();
        bool hasStencilComponent(VkFormat format);
        VkCommandBuffer beginSingleTimeCommands();
        VkShaderModule createShaderModule(const std::vector<char>& code);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        bool isDeviceSuitable(VkPhysicalDevice device);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        std::vector<const char*> getRequiredExtensions();
        bool checkValidationLayerSupport();
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        static std::vector<char> readFile(const std::string& filename);
        static VulkanGraphicEngine* GetInstance();

    public:
        VulkanGraphicEngine(Application* engineWindow);
        ~VulkanGraphicEngine();

    public:
        static void setVertexBuffer(VertexBuffer* buffer);
        static void setIndexBuffer(IndexBuffer* buffer);
        static void setViewAndProjectionMatrices(glm::mat4 view, glm::mat4 proj);
        static void setPushConstant(PushConstantData pushConstant);
        static void setTexture(uint32_t binding, VulkanTexture* texture);
        static void drawFrame();
        static VkCommandBuffer beginFrame();
        static void endFrame();
        static VkResult __stdcall waitIdle();
        static void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        static void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        static void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
        static void DestroyBuffer(VkBuffer buffer);
        static void FreeMemory(VkDeviceMemory memory);
        static void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
        static VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
        static void transitionImageLayout(VkImage image, VkFormat format, VkImageAspectFlags aspectMask, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
        static void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
        static VkDevice GetLogicalDevice();
        static VkPhysicalDevice GetPhysicalDevice();


#ifdef DEBUG
    private:
        VkDebugUtilsMessengerEXT debugMessenger;

    private:
        void setupDebugMessenger();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
        static void logPhysicalDeviceProperties(VkPhysicalDevice phsicalDevice);

#endif
	};
}