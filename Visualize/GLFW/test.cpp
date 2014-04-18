#include <GLFW/glfw3.h>
#include <GL/glext.h>
#include <iostream>
#include "Window.h"

using namespace ZNAC;
using namespace Visualize;

int main()
{
	Window wnd("test", true);
	PFNGLDEBUGMESSAGECALLBACKPROC v = (PFNGLDEBUGMESSAGECALLBACKPROC)glfwGetProcAddress("glDebugMessageCallback");
	std::cout << ((v == nullptr)?"zannnenndesita":"omedetou") << std::endl;
	v(0, 0);
	glClearColor(1, 1, 1, 0);
	while(wnd)
	{
		wnd.Update();
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(wnd);
	}
}
