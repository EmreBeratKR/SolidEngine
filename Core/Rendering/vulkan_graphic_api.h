#pragma once

#ifndef NDEBUG
#define DEBUG 1
#endif

#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"

#include <string>
#include <vector>
#include <optional>
#include <set>


namespace Engine::Rendering
{
	class VulkanGraphicApi
	{
	public:
		VulkanGraphicApi(GLFWwindow* window);
		~VulkanGraphicApi();

		VkDevice getLogicalDevice();

	private:
		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphics;
			std::optional<uint32_t> present;


			std::set<uint32_t> toSet()
			{
				return std::set<uint32_t>
				{
					graphics.value(),
					present.value()
				};
			}

			uint32_t* toArray()
			{
				uint32_t arr[] = { graphics.value(), present.value() };

				return arr;
			}

			bool isCompleted()
			{
				return graphics.has_value() && present.has_value();
			}
		};

		struct SwapChainSupportDetails 
		{
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;

			bool isEnough()
			{
				return !formats.empty() && !presentModes.empty();
			}
		};

		void init(GLFWwindow* window);
		void createInstance();
		void cleanup();
		void createSurface(GLFWwindow* window);
		void selectPhysicalDevice();
		void createLogicalDevice();
		void createSwapChain(GLFWwindow* window);
		void createImageViews();
		void createRenderPipeline(const std::string& vertShaderFilePath, const std::string& fragShaderFilePath);
		void createShaderStages();

		static int getPhysicalDeviceSuitabilityScore(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, std::vector<const char*> deviceExtensions);
		static VkPhysicalDevice getBestSuitablePhysicalDevice(VkInstance instance, VkSurfaceKHR surface, std::vector<const char*> deviceExtensions);
		static QueueFamilyIndices getQueueFamilyIndices(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
		static bool checkDeviceExtensionSupport(VkPhysicalDevice physicalDevice, std::vector<const char*> deviceExtensions);
		static SwapChainSupportDetails getPhysicalDeviceSwapChainSupportDetails(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
		static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		static VkExtent2D chooseSwapExtent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities);
		static std::vector<char> readShaderFile(const std::string& filePath);
		static VkShaderModule createShaderModule(VkDevice logicalDevice, const std::vector<char>& code);

		VkInstance instance;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice logicalDevice;
		VkQueue graphicsQueue;
		VkQueue presentQueue;
		VkSurfaceKHR surface;
		VkSwapchainKHR swapChain;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		std::vector<VkImage> swapChainImages;
		std::vector<VkImageView> swapChainImageViews;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;

		const std::vector<const char*> deviceExtensions = 
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

#ifdef DEBUG
		void setupDebugMessenger();
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		VkResult CreateDebugUtilsMessengerEXT(
			VkInstance instance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator,
			VkDebugUtilsMessengerEXT* pDebugMessenger);
		void DestroyDebugUtilsMessengerEXT(
			VkInstance instance,
			VkDebugUtilsMessengerEXT debugMessenger,
			const VkAllocationCallbacks* pAllocator);

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);
		static void logPhysicalDeviceProperties(VkPhysicalDevice physicalDevice);

		VkDebugUtilsMessengerEXT debugMessenger;

		const std::vector<const char*> validationLayers =
		{
			"VK_LAYER_KHRONOS_validation"
		};
#endif
	};
}
