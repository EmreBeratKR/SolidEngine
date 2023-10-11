#pragma once

#include <string>
#include <GLFW/glfw3.h>


namespace Engine
{
	class EngineWindow
	{
		public:
			EngineWindow(int width, int height, std::string title);
			~EngineWindow();

		private:
			void init();
			void run();
			bool shouldClose();
			void close();

			const int WIDTH;
			const int HEIGHT;
			const std::string TITLE;

			GLFWwindow* m_Window;
	};
}
