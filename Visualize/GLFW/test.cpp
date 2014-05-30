#include "../PNG/GLCapture.h"
#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>
#include <GL/glext.h>
#include <iostream>
#include "Window.h"
#include "Capture.h"
#include "Camera.h"
#include "Joystick.h"

using namespace ZNAC;
using namespace Visualize;

int main()
{
	Window wnd;
	Camera camera;
	FTGLPixmapFont font("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
	if(font.Error())
		std::cout << "font error" << std::endl;
	if(!font.FaceSize(10))
		std::cout << "font error" << std::endl;
	font.UseDisplayList(false);
	if(!font.CharMap(ft_encoding_unicode))
		std::cout << "font error" << std::endl;

	Ortho ort(4, 4, 100);
	ort.Set();
	//camera.Pitch(0.2);
	//camera.Roll(1.57);
	//camera.Yaw(0.2);
	camera.Shift(0.2, 0, 0);

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	camera.Set();

	glColor3d(0, 0, 1.0);
	glBegin(GL_LINE_STRIP);
	glVertex2d(1, 0);
	glVertex2d(-1, 0);
	glVertex2d(0, 1);
	glVertex2d(0, -1);
	glEnd();

	glRasterPos2f(0, 0);
	font.Render("hello ftgl");

	glfwSwapBuffers(wnd);

//	Capture c(wnd);

//	c.Get();

//	PNGWriter w("./", "test", c.Width, c.Height);

//	w << c.Image;
//
	glEnd();
	glBegin(-2);
	GLCapture("testpng.png", 0, 0, 640, 480);

	while(wnd)
	{
		wnd.Update();
	}
}
