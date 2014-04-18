#ifndef ZARATH_ZNAC_VISUALIZE_GLFW_WINDOW_H
#define ZARATH_ZNAC_VISUALIZE_GLFW_WINDOW_H

#include <GLFW/glfw3.h>

namespace ZNAC
{
	namespace Visualize
	{
		namespace GLFW
		{
			class Window
			{
			public:
				Window();
				Window(unsigned int width, unsigned int height, const char *title, bool isFullScreen = false);
				~Window();
	
				void Update();

				operator bool();
				operator GLFWwindow*();
			protected:
				GLFWwindow *wnd;
				bool shouldClose;
	
			private:
				static unsigned int wnd_nums;
				virtual void update();
			};
		}
	}
}

#endif
