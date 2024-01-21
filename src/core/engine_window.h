#pragma once

#include "Rendering/vulkan_graphic_engine.fwd.h"
#include "Rendering/vulkan_graphic_engine.h"

#include <string>
#include <GLFW/glfw3.h>


namespace Engine
{
	class EngineWindow
	{
	public:
		static EngineWindow* main;

	private:
		const std::string TITLE;

		GLFWwindow* m_Window;
		Rendering::VulkanGraphicEngine* m_GraphicEngine;
		int width;
		int height;
		float aspectRatio;
		bool framebufferResized = false;

	private:
		void init();
		bool shouldClose();
		void close();

		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	public:
		EngineWindow(int width, int height, std::string title);
		~EngineWindow();

	public:
		void run();
		void setGraphicEngine(Rendering::VulkanGraphicEngine* graphicApi);
		GLFWwindow* getGLFWWindow();
		float getAspectRatio();
		bool getFrameBufferResized();
		void setFrameBufferResized(bool value);
	};
}
