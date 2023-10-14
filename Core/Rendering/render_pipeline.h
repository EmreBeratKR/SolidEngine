#pragma once

#include "vulkan_graphic_api.h";
#include "vulkan/vulkan.h"

#include <string>
#include <vector>


namespace Engine::Rendering
{
	class RenderPipeline
	{
	public:
		RenderPipeline(VulkanGraphicApi graphicApi, const std::string& vertShaderFilePath, const std::string& fragShaderFilePath);
		~RenderPipeline();

	private:
		VulkanGraphicApi graphicApi;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;


		void init(const std::string& vertShaderFilePath, const std::string& fragShaderFilePath);
		void createShaderStages();

		static std::vector<char> readFile(const std::string& filePath);
		static VkShaderModule createShaderModule(VkDevice logicalDevice, const std::vector<char>& code);
	};
}