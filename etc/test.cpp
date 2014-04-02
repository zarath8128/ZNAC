#include <iostream>
#include <random>
#include "Visualize/GLFW/Window.h"
#include "DelaunayTriangulation.h"

using namespace ZNAC;
using namespace ZNAC::etc;
using namespace ZNAC::GLFW;

int main()
{
	std::mt19937 rnd(1);
	std::uniform_real_distribution<double> aria(-0.8, 0.8);

	constexpr unsigned int num = 100;
	constexpr unsigned int dim = 2;


	Array<Point<dim>> points;
	for(unsigned int i = 0; i < num; ++i)
		points << Point<dim>(aria(rnd), aria(rnd));

	Array<Simplex<dim>> triangles;

	DelaunaySimplexion(points, triangles);

	Window w;
	glClearColor(1, 1, 1, 1);
	while(w)
	{
		w.Update();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		glPointSize(5);
		glBegin(GL_POINTS);
		glColor3d(0, 0, 0);
		for(unsigned int i = 0; i < 100; ++i)
			glVertex2d(points[i][0], points[i][1]);
		glEnd();

		glfwSwapBuffers(w);
	}
	return 0;
}
