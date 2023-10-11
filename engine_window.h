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

			int m_Width;
			int m_Height;
			std::string m_Title;
			GLFWwindow* m_Window;
	};
}
