#pragma once

#include "vulkan/vulkan.h"


namespace Engine::Rendering
{
	class VulkanGraphicApi
	{
	public:
		VulkanGraphicApi();
		~VulkanGraphicApi();

	private:
		void init();
		void cleanup();

		VkInstance instance;
	};
}
