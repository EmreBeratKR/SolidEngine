#include "application.h"
#include "vulkan_graphic_engine.h"


namespace Engine
{
	Application::Application(int width, int height, std::string title)
		: width(width), height(height), TITLE(title)
	{
		init();
	}

	Application::~Application()
	{
		close();
	}


	Application* Application::instance{nullptr};


	void Application::run()
	{
		auto vulkan = Rendering::VulkanGraphicEngine::GetInstance();

		while (!shouldClose())
		{
			glfwPollEvents();
			layerStack.OnUpdate();
			vulkan->beginFrame();
			layerStack.OnRender();
			vulkan->endFrame();
		}

		vulkan->waitIdle();
		close();
	}

	GLFWwindow* Application::getGLFWWindow()
	{
		return m_Window;
	}

	float Application::getAspectRatio()
	{
		return aspectRatio;
	}

	bool Application::getFrameBufferResized()
	{
		return framebufferResized;
	}

	void Application::setFrameBufferResized(bool value)
	{
		framebufferResized = value;
	}


	void Application::init()
	{
		instance = this;

		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		aspectRatio = (float) width / height;
		m_Window = glfwCreateWindow(width, height, TITLE.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, framebufferResizeCallback);
	}

	bool Application::shouldClose()
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Application::close()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}


	void Application::framebufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

		app->aspectRatio = (float) width / height;
		app->width = width;
		app->height = height;
		app->framebufferResized = true;
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		layerStack.PopLayer(layer);
	}
}