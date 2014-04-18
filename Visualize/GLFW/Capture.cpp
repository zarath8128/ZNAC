#include "Capture.h"

namespace ZNAC
{
	namespace Visualize
	{
		Capture::Capture(GLFWwindow *wnd)
			:Width(w), Height(h), Image(image), wnd(wnd), w(0), h(0), image(nullptr), data(nullptr){}

		void Capture::Get()
		{
			delete [] data;
			delete [] image;
			data = nullptr;
			image = nullptr;

			glfwGetFramebufferSize(wnd, &w, &h);

			data = new unsigned char[4*w*h];
			image = new unsigned char*[h];

			for(int i = 0; i < h; ++i)
				image[i] = data + i*w*4;

			for(int i = 0; i < h/2; ++i)
			{
				unsigned char * tmp;
				tmp = image[i];
				image[i] = image[h - i - 1];
				image[h - i - 1] = tmp;
			}

			glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
	}
}
