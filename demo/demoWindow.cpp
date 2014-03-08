#include "demoWindow.h"
#include <cmath>
#include <iostream>

using namespace ZNAC::GLFW;
using namespace ZNAC::PDE;

constexpr double width = 40;
constexpr double xmin = -20, ymin = -20;
constexpr double umax = 1, umin = -1;
constexpr unsigned int N = 100;

demoWindow::demoWindow():Window(1080, 720, "demo"), c(wnd), F(2, N, N), D(F, width, width), rk(F, 0.05*D.dx*D.dx, 1e-6, LA::supNorm<double>())
{
	glClearColor(1, 1, 1, 1);
	for(unsigned int r = 0; r < F.Ny; ++r)
		for(unsigned int c = 0; c < F.Nx; ++c)
		{
			double x = c*D.dx + xmin;
			double y = r*D.dy + ymin;
			F[r*F.Nx + c] = ((-16 < x && x < -15)?(0.22):(0));
			F[F.Nx*F.Ny + r*F.Nx + c] = ((x < -18)?(0.0):(0));
		}
	c.Zoom(2.2);
}

void demoWindow::update()
{
	static int i = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	c.Set(j);

	for(unsigned int r = 0; r < F.Ny - 1; ++r)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(unsigned int c = 0; c < F.Nx; ++c)
		{
			glColor3d(0, (F(0, r, c) - umin)*1/(umax - umin), (F(0, r, c) - umin)*1/(umax - umin));
			glVertex3d(c*D.dx+xmin, r*D.dy+ymin, 100*F(0, r, c));
			glColor3d(0, (F(0, r + 1, c) - umin)*1/(umax - umin), (F(0, r + 1, c) - umin)*1/(umax - umin));
			glVertex3d(c*D.dx+xmin, (r + 1)*D.dy+ymin, 10*F(0, r + 1, c));
		}
		glEnd();
	}

	for(unsigned int r = 0; r < F.Ny - 1; ++r)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(unsigned int c = 0; c < F.Nx; ++c)
		{
			glColor3d((F(0, r, c) - umin)*1/(umax - umin), 0, (F(0, r, c) - umin)*1/(umax - umin));
			glVertex3d(c*D.dx+xmin, r*D.dy+ymin, 100*F(1, r, c));
			glColor3d((F(0, r + 1, c) - umin)*1/(umax - umin), 0, (F(0, r + 1, c) - umin)*1/(umax - umin));
			glVertex3d(c*D.dx+xmin, (r + 1)*D.dy+ymin, 10*F(1, r + 1, c));
		}
		glEnd();
	}


	glfwSwapBuffers(wnd);
	rk(D, F, F, 0, 0.001);
}
