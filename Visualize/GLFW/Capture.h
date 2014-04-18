#ifndef ZARATH_ZNAC_VISUALIZE_GLFW_CAPTURE_H
#define ZARATH_ZNAC_VISUALIZE_GLFW_CAPTURE_H

#include <GL/gl.h>
#include <GLFW/glfw3.h>

namespace ZNAC
{
	namespace Visualize
	{
		class Capture
		{
		public:
			int &Width, &Height;
			unsigned char ** const &Image;

			Capture(GLFWwindow *wnd);

			void Get();

		private:
			GLFWwindow *wnd;
			int w, h;
			unsigned char **image;
			unsigned char *data;
		};
	}
}

#endif
