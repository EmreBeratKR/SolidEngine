#pragma once

#include <string>
#include <vector>


namespace Engine::Rendering
{
	class RenderPipeline
	{
	public:
		RenderPipeline(const std::string& vertShaderFilePath, const std::string& fragShaderFilePath);
		~RenderPipeline();

	private:
		static std::vector<char> readFile(const std::string& filePath);

		void create(const std::string& vertShaderFilePath, const std::string& fragShaderFilePath);
	};
}