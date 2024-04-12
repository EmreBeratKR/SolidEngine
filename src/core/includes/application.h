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
		void initWindow();
		void initInputs();
		bool shouldClose();
		void close();
		void getCurrentMousePosition(double* x, double* y);

		static void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void onFrameBufferResizeCallback(GLFWwindow* window, int width, int height);

	public:
		Application(int width, int height, std::string title);
		~Application();

	public:
		void run();
		GLFWwindow* getGLFWWindow();
		float getAspectRatio();
		bool getFrameBufferResized();
		void setFrameBufferResized(bool value);
		void pushLayer(Layer* layer);
		void popLayer(Layer* layer);

		static int getKeyCurrentState(int key);
		static int getKeyPreviousState(int key);
		static int getMouseButtonCurrentState(int key);
		static int getMouseButtonPreviousState(int key);
		static int getMouseX();
		static int getMouseY();
		static int getMouseDeltaX();
		static int getMouseDeltaY();
		static void setCursorNormal();
		static void setCursorLocked();
	};
}
