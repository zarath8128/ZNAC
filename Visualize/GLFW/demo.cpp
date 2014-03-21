#include "demo.h"
#include "../libpng/PNGWriter.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <iostream>

using namespace ZNAC::GLFW;

#ifndef M_PI
#define M_PI 3.14159265358979323
#endif

demoWindow::demoWindow():Window(640, 640, "demo", false), c(wnd)
{
	glClearColor(1, 1, 1, 1);
}

struct vec3
{
	double x, y, z;
};

vec3 pos(int i, int j)
{
	vec3 ret;
	ret.x = cos(i/255.*2*M_PI)*cos(j/255.*2*M_PI);
	ret.y = sin(i/255.*2*M_PI);
	ret.z = cos(i/255.*2*M_PI)*sin(j/255.*2*M_PI);
	return ret;
}

void set(vec3 p)
{
	glColor3d((p.x + 1)*0.5, (p.y + 1)*0.5, (p.z + 1)*0.5);
	glVertex3d(p.x, p.y, p.z);
}

void demoWindow::update()
{
	int range;
	const float *axes = j.Axes(range);
	const unsigned char *buttons = j.Buttons(range);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, 0, 4);

/*	c.Yaw(axes[0]*0.1);
	c.Pitch(axes[1]*0.1);
	c.Roll(axes[5]*0.1);
	c.Zoom(axes[6]*0.01);
*/	
	c.Set(j);

	glBegin(GL_LINES);
	glColor3d(1, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 100, 0);
	glColor3d(0, 1, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 100);
	glColor3d(0, 0, 1);
	glVertex3d(0, 0, 0);
	glVertex3d(100, 0, 0);
	glEnd();

	for(int i = 0; i < 256; ++i)
	{
	glBegin(GL_TRIANGLE_STRIP);
		for(int j = 0; j < 256; ++j)
		{
			set(pos(i, j));
			set(pos(i + 1, j));
		}
	glEnd();
	}

	glfwSwapBuffers(wnd);

	ZNAC::libpng::GLCapture("tetete.png", 0, 0, 640, 640);
}
