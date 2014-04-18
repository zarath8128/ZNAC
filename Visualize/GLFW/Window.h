#ifndef ZARATH_ZNAC_VISUALIZE_WINDOW_H
#define ZARATH_ZNAC_VISUALIZE_WINDOW_H

#include <GLFW/glfw3.h>

namespace ZNAC
{
	namespace Visualize
	{
		class Window
		{
		public:
			const int &Width, &Height, &X, &Y, &fbWidth, &fbHeight;

			Window();
			Window(bool IsFullScreen);
			Window(const char *title, bool IsVisible = true);
			Window(int width, int height, bool IsVisible = true);
			Window(int width, int height, const char *title, bool IsVisible = true);
			Window(int width, int height, int x, int y, bool IsVisible = true);
			Window(int width, int height, int x, int y, const char *title, bool IsVisible = true);
			~Window();

			void Update();

			operator bool();
			operator GLFWwindow*();

		protected:
			GLFWwindow *wnd;

		private:
			int width, height, x, y, fbwidth, fbheight;

			static unsigned int wnd_nums;
			static int context_major, context_minor;

			friend void glfw_wnd_pos_func(GLFWwindow*, int, int);
			friend void glfw_wnd_size_func(GLFWwindow*, int, int);
			friend void glfw_wnd_fbsize_func(GLFWwindow*, int, int);

			Window(int width, int height, int x, int y, const char *title,  bool isFullScreen, bool IsVisible);
		};
	}
}

#endif
