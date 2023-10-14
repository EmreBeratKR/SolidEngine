#pragma once

#ifndef NDEBUG
#define DEBUG 1
#endif

#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"

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

			bool isCompleted()
			{
				return graphics.has_value() && present.has_value();
			}
		};

		void init(GLFWwindow* window);
		void createInstance();
		void cleanup();
		void createSurface(GLFWwindow* window);
		void selectPhysicalDevice();
		void createLogicalDevice();

		static int getPhysicalDeviceSuitabilityScore(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
		static VkPhysicalDevice getBestSuitablePhysicalDevice(VkInstance instance, VkSurfaceKHR surface);
		static QueueFamilyIndices getQueueFamilyIndices(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

		VkInstance instance;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice logicalDevice;
		VkQueue graphicsQueue;
		VkQueue presentQueue;
		VkSurfaceKHR surface;

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
