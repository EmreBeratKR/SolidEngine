#include "engine_window.h"


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
			m_GraphicEngine->drawFrame();
		}

		m_GraphicEngine->waitIdle();
		close();
	}

	void EngineWindow::setGraphicEngine(Rendering::VulkanGraphicEngine* graphicEngine)
	{
		m_GraphicEngine = graphicEngine;
	}

	GLFWwindow* EngineWindow::getGLFWWindow()
	{
		return m_Window;
	}

	bool EngineWindow::getFrameBufferResized()
	{
		return framebufferResized;
	}

	void EngineWindow::setFrameBufferResized(bool value)
	{
		framebufferResized = value;
	}


	void EngineWindow::init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		m_Window = glfwCreateWindow(WIDTH, HEIGHT, TITLE.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, framebufferResizeCallback);
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


	void EngineWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		auto app = reinterpret_cast<EngineWindow*>(glfwGetWindowUserPointer(window));

		app->framebufferResized = true;
	}
}