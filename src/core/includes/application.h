#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include <unordered_map>


#include "layer_stack.h"


namespace Engine
{
	class Application
	{
	public:
		static Application* instance;

	private:
		const std::string TITLE;

		GLFWwindow* m_Window;
		int width;
		int height;
		float aspectRatio;
		bool framebufferResized = false;
		LayerStack layerStack;


	private:
		void init();
		bool shouldClose();
		void close();
		void GetCurrentMousePosition(double* x, double* y);

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	public:
		Application(int width, int height, std::string title);
		~Application();

	public:
		void run();
		GLFWwindow* getGLFWWindow();
		float getAspectRatio();
		bool getFrameBufferResized();
		void setFrameBufferResized(bool value);
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		static int GetKeyCurrentState(int key);
		static int GetKeyPreviousState(int key);
		static int GetMouseButtonCurrentState(int key);
		static int GetMouseButtonPreviousState(int key);
		static int GetMouseX();
		static int GetMouseY();
		static int GetMouseDeltaX();
		static int GetMouseDeltaY();
	};
}
