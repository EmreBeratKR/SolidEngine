#include "application.h"
#include "vulkan_graphic_engine.h"


namespace Engine
{
	static std::unordered_map<int, int> ms_CurrentKeyStates;
	static std::unordered_map<int, int> ms_PreviousKeyStates;
	static std::unordered_map<int, int> ms_CurrentMouseButtonStates;
	static std::unordered_map<int, int> ms_PreviousMouseButtonStates;
	static double ms_MouseX;
	static double ms_MouseY;
	static double ms_MouseDeltaX;
	static double ms_MouseDeltaY;


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
			auto previousMouseX = ms_MouseX;
			auto previousMouseY = ms_MouseY;
			getCurrentMousePosition(&ms_MouseX, &ms_MouseY);
			ms_MouseDeltaX = ms_MouseX - previousMouseX;
			ms_MouseDeltaY = ms_MouseY - previousMouseY;
			layerStack.OnUpdate();
			Rendering::VulkanGraphicEngine::beginFrame();
			layerStack.OnRender();
			Rendering::VulkanGraphicEngine::endFrame();

			for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; key++) 
			{
				ms_PreviousKeyStates[key] = ms_CurrentKeyStates[key];
			}

			for (int button = GLFW_MOUSE_BUTTON_1; button <= GLFW_MOUSE_BUTTON_LAST; button++)
			{
				ms_PreviousMouseButtonStates[button] = ms_CurrentMouseButtonStates[button];
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

	void Application::pushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}

	void Application::popLayer(Layer* layer)
	{
		layerStack.PopLayer(layer);
	}


	void Application::init()
	{
		instance = this;

		initWindow();
		initInputs();
	}

	void Application::initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		aspectRatio = (float) width / height;
		m_Window = glfwCreateWindow(width, height, TITLE.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(m_Window, this);
	}

	void Application::initInputs()
	{
		for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; key++) 
		{
            ms_CurrentKeyStates[key] = glfwGetKey(m_Window, key);
        }

		for (int button = GLFW_MOUSE_BUTTON_1; button <= GLFW_MOUSE_BUTTON_LAST; button++)
		{
			ms_CurrentMouseButtonStates[button] = glfwGetMouseButton(m_Window, button);
		}

		getCurrentMousePosition(&ms_MouseX, &ms_MouseY);

		glfwSetKeyCallback(m_Window, onKeyCallback);
		glfwSetMouseButtonCallback(m_Window, onMouseButtonCallback);
		glfwSetFramebufferSizeCallback(m_Window, onFrameBufferResizeCallback);
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

	void Application::getCurrentMousePosition(double* x, double* y)
	{
		glfwGetCursorPos(m_Window, x, y);
		*y = height - *y;
	}


	int Application::getKeyCurrentState(int key)
	{
		return ms_CurrentKeyStates[key];
	}

	int Application::getKeyPreviousState(int key)
	{
		return ms_PreviousKeyStates[key];
	}

	int Application::getMouseButtonCurrentState(int button)
	{
		return ms_CurrentMouseButtonStates[button];
	}

	int Application::getMouseButtonPreviousState(int button)
	{
		return ms_PreviousMouseButtonStates[button];
	}

	int Application::getMouseX()
	{
		return ms_MouseX;
	}

	int Application::getMouseY()
	{
		return ms_MouseY;
	}

	int Application::getMouseDeltaX()
	{
		return ms_MouseDeltaX;
	}

	int Application::getMouseDeltaY()
	{
		return ms_MouseDeltaY;
	}

	void Application::onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		ms_CurrentKeyStates[key] = action;
	}

	void Application::onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		ms_CurrentMouseButtonStates[button] = action;
	}

	void Application::onFrameBufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

		app->aspectRatio = (float) width / height;
		app->width = width;
		app->height = height;
		app->framebufferResized = true;
	}
}