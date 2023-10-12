#include "render_pipeline.h"

#include <fstream>
#include <stdexcept>
#include <iostream>


namespace Engine::Rendering
{
	RenderPipeline::RenderPipeline(const std::string& vertShaderFilePath, const std::string& fragShaderFilePath)
	{
		create(vertShaderFilePath, fragShaderFilePath);
	}

	RenderPipeline::~RenderPipeline()
	{

	}


	void RenderPipeline::create(const std::string& vertShaderFilePath, const std::string& fragShaderFilePath)
	{
		auto vertShaderFile = readFile(vertShaderFilePath);
		auto fragShaderFile = readFile(fragShaderFilePath);

		std::cout << "Vertex Shader File Size: " << vertShaderFile.size() << '\n';
		std::cout << "Fragment Shader File Size: " << fragShaderFile.size() << '\n';
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
}