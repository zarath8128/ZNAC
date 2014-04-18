#include <GLFW/glfw3.h>
#include <GL/glext.h>
#include <iostream>
#include "Window.h"
#include "Capture.h"
#include "../PNG/PNGWriter.h"

using namespace ZNAC;
using namespace Visualize;

int main()
{
	Window wnd("test", true);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3d(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2d(1, 0);
	glVertex2d(-1, 0);
	glVertex2d(0, 1);
	glVertex2d(0, -1);
	glEnd();

	glfwSwapBuffers(wnd);

	Capture c(wnd);

	c.Get();

	PNGWriter w("./", "test", c.Width, c.Height);

	w << c.Image;

	while(wnd)
	{
		wnd.Update();
	}
}
