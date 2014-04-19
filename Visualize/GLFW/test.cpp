#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>
#include <GL/glext.h>
#include <iostream>
#include "Window.h"
#include "Capture.h"
#include "Joystick.h"
#include "../PNG/PNGWriter.h"

using namespace ZNAC;
using namespace Visualize;

int main()
{
	Window wnd;
	FTGLPixmapFont font("/usr/share/fonts/truetype/kochi/kochi-gothic.ttf");
	if(font.Error())
		std::cout << "font error" << std::endl;
	if(!font.FaceSize(190))
		std::cout << "font error" << std::endl;
	font.UseDisplayList(false);
	if(!font.CharMap(ft_encoding_unicode))
		std::cout << "font error" << std::endl;

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3d(0, 0, 1.0);
/*	glBegin(GL_LINE_STRIP);
	glVertex2d(1, 0);
	glVertex2d(-1, 0);
	glVertex2d(0, 1);
	glVertex2d(0, -1);
	glEnd();
*/
	glMatrixMode(GL_MODELVIEW);
	glRasterPos2f(0, 0.1);
	font.Render("hello ftgl");

	glfwSwapBuffers(wnd);

	Capture c(wnd);

	c.Get();

	PNGWriter w("./", "test", c.Width, c.Height);

//	w << c.Image;

	while(wnd)
	{
		wnd.Update();
	}
}
