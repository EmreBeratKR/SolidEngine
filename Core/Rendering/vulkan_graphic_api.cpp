#include "vulkan_graphic_api.h"
#include "GLFW/glfw3.h"

#include <stdexcept>


namespace Engine::Rendering
{
	VulkanGraphicApi::VulkanGraphicApi()
	{
		init();
	}

	VulkanGraphicApi::~VulkanGraphicApi()
	{
		cleanup();
	}


	void VulkanGraphicApi::init()
	{
		VkApplicationInfo appInfo{};

		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Game Engine Editor";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Gamegine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};

		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;

		VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan instance!");
		}
	}

	void VulkanGraphicApi::cleanup()
	{
		vkDestroyInstance(instance, nullptr);
	}
}