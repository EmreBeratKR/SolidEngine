#pragma once

#ifndef NDEBUG
#define DEBUG 1
#endif

#include "vulkan/vulkan.h"

#include <vector>


namespace Engine::Rendering
{
	class VulkanGraphicApi
	{
	public:
		VulkanGraphicApi();
		~VulkanGraphicApi();

	private:
		void init();
		void createInstance();
		void selectPhysicalDevice();
		void cleanup();

		static int getPhysicalDeviceSuitabilityScore(VkPhysicalDevice physicalDevice);
		static VkPhysicalDevice getBestSuitablePhysicalDevice(VkInstance instance);

		VkInstance instance;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

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
