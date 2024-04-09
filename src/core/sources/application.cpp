#include "application.h"
#include "vulkan_graphic_engine.h"


namespace Engine
{
	static std::unordered_map<int, int> ms_CurrentKeyStates;
	static std::unordered_map<int, int> ms_PreviousKeyStates;
	static double ms_MouseX;
	static double ms_MouseY;


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
		while (!shouldClose())
		{
			glfwPollEvents();
			glfwGetCursorPos(m_Window, &ms_MouseX, &ms_MouseY);
			ms_MouseY = height - ms_MouseY;
			layerStack.OnUpdate();
			Rendering::VulkanGraphicEngine::beginFrame();
			layerStack.OnRender();
			Rendering::VulkanGraphicEngine::endFrame();

			for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; key++) 
			{
				ms_PreviousKeyStates[key] = ms_CurrentKeyStates[key];
			}
		}

		Rendering::VulkanGraphicEngine::waitIdle();
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

		for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; key++) 
		{
            ms_CurrentKeyStates[key] = glfwGetKey(m_Window, key);
        }

		glfwSetKeyCallback(m_Window, KeyCallback);
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


	int Application::GetKeyCurrentState(int key)
	{
		return ms_CurrentKeyStates[key];
	}

	int Application::GetKeyPreviousState(int key)
	{
		return ms_PreviousKeyStates[key];
	}

	int Application::GetMouseX()
	{
		return ms_MouseX;
	}

	int Application::GetMouseY()
	{
		return ms_MouseY;
	}


	void Application::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		ms_CurrentKeyStates[key] = action;
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