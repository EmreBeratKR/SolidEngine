#pragma once

#include "Rendering/vulkan_graphic_api.h"

#include <string>
#include <GLFW/glfw3.h>


namespace Engine
{
	class EngineWindow
	{
	public:
		EngineWindow(int width, int height, std::string title);
		~EngineWindow();

		void run();
		void setGraphicApi(Rendering::VulkanGraphicApi* graphicApi);
		GLFWwindow* getGLFWWindow();

	private:
		void init();
		bool shouldClose();
		void close();

		const int WIDTH;
		const int HEIGHT;
		const std::string TITLE;

		GLFWwindow* m_Window;
		Rendering::VulkanGraphicApi* m_GraphicApi;
	};
}
