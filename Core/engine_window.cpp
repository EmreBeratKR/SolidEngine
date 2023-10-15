#include "engine_window.h"

#include <string>
#include <GLFW/glfw3.h>


namespace Engine
{
	EngineWindow::EngineWindow(int width, int height, std::string title)
		: WIDTH(width), HEIGHT(height), TITLE(title)
	{
		init();
	}

	EngineWindow::~EngineWindow()
	{
		close();
	}


	void EngineWindow::run()
	{
		while (!shouldClose())
		{
			glfwPollEvents();
			m_GraphicApi->drawFrame();
		}

		m_GraphicApi->waitIdle();
		close();
	}

	void EngineWindow::setGraphicApi(Rendering::VulkanGraphicApi* graphicApi)
	{
		m_GraphicApi = graphicApi;
	}

	GLFWwindow* EngineWindow::getGLFWWindow()
	{
		return m_Window;
	}


	void EngineWindow::init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_Window = glfwCreateWindow(WIDTH, HEIGHT, TITLE.c_str(), nullptr, nullptr);
	}

	bool EngineWindow::shouldClose()
	{
		return glfwWindowShouldClose(m_Window);
	}

	void EngineWindow::close()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
}