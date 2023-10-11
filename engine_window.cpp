#include "engine_window.h"

#include <string>
#include <GLFW/glfw3.h>


namespace Engine
{
	EngineWindow::EngineWindow(int width, int height, std::string title)
		: m_Width(width), m_Height(height), m_Title(title)
	{
		init();
		run();
	}

	EngineWindow::~EngineWindow()
	{

	}


	void EngineWindow::init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
	}

	void EngineWindow::run()
	{
		while (!shouldClose())
		{
			glfwPollEvents();
		}

		close();
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