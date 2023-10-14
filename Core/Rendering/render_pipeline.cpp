#include "render_pipeline.h"

#include <fstream>
#include <stdexcept>
#include <iostream>


namespace Engine::Rendering
{
	RenderPipeline::RenderPipeline(VulkanGraphicApi graphicApi, const std::string& vertShaderFilePath, const std::string& fragShaderFilePath)
		: graphicApi{graphicApi}
	{
		init(vertShaderFilePath, fragShaderFilePath);
	}

	RenderPipeline::~RenderPipeline()
	{
		auto logicalDevice = graphicApi.getLogicalDevice();

		vkDestroyShaderModule(logicalDevice, fragShaderModule, nullptr);
		vkDestroyShaderModule(logicalDevice, vertShaderModule, nullptr);
	}


	void RenderPipeline::init(const std::string& vertShaderFilePath, const std::string& fragShaderFilePath)
	{
		auto logicalDevice = graphicApi.getLogicalDevice();
		auto vertShaderFile = readFile(vertShaderFilePath);
		auto fragShaderFile = readFile(fragShaderFilePath);

		vertShaderModule = createShaderModule(logicalDevice, vertShaderFile);
		fragShaderModule = createShaderModule(logicalDevice, fragShaderFile);

		createShaderStages();
	}

	void RenderPipeline::createShaderStages()
	{
		VkPipelineShaderStageCreateInfo vertShaderStageInfo{};

		vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertShaderStageInfo.module = vertShaderModule;
		vertShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo fragShaderStageInfo{};

		fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragShaderStageInfo.module = fragShaderModule;
		fragShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };
	}


	std::vector<char> RenderPipeline::readFile(const std::string& filePath)
	{
		std::ifstream fileStream(filePath, std::ios::ate | std::ios::binary);

		if (!fileStream.is_open())
		{
			throw std::runtime_error("failed to open file at path => " + filePath);
		}

		size_t fileSize = static_cast<size_t>(fileStream.tellg());
		std::vector<char> charBuffer(fileSize);

		fileStream.seekg(0);
		fileStream.read(charBuffer.data(), fileSize);
		fileStream.close();

		return charBuffer;
	}

	VkShaderModule RenderPipeline::createShaderModule(VkDevice logicalDevice, const std::vector<char>& code)
	{
		VkShaderModule shaderModule;
		VkShaderModuleCreateInfo createInfo{};

		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		if (vkCreateShaderModule(logicalDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create shader module!");
		}

		return shaderModule;
	}
}