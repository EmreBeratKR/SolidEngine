#pragma once

#include "Rendering/vulkan_graphic_engine.h"

#include <string>
#include <GLFW/glfw3.h>


namespace Engine
{
	class EngineWindow
	{
	private:
		const int WIDTH;
		const int HEIGHT;
		const std::string TITLE;

		GLFWwindow* m_Window;
		Rendering::VulkanGraphicEngine* m_GraphicEngine;

	private:
		void init();
		bool shouldClose();
		void close();

	public:
		EngineWindow(int width, int height, std::string title);
		~EngineWindow();

	public:
		void run();
		void setGraphicApi(Rendering::VulkanGraphicEngine* graphicApi);
		GLFWwindow* getGLFWWindow();
	};
}
