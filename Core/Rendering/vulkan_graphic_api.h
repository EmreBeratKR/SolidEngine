#pragma once

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
		void cleanup();
		bool checkValidationLayerSupport();

		VkInstance instance;

		const std::vector<const char*> validationLayers = 
		{
			"VK_LAYER_KHRONOS_validation"
		};

#ifdef NDEBUG
		const bool enableValidationLayers = false;
#else
		const bool enableValidationLayers = true;
#endif
	};
}
