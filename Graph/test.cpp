#include <iostream>
#include "../Visualize/GLFW/Window.h"
#include "Graph.h"

using namespace ZNAC;
using namespace ZNAC::Graph;
using namespace ZNAC::GLFW;

	Vertex<Vector<2>> w;

class testWindow
	:public Window
{
public:
private:
	void update()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glOrtho(-.1, 1.1, -.1, 1.1, 0, 1);
		glPointSize(4);
		glColor3d(0, 0, 0);
		glBegin(GL_POINTS);
		for(unsigned int i = 0; i < w.Used; ++i)
			glVertex2d(w[i][0], w[i][1]);
		glEnd();
		glfwSwapBuffers(wnd);
	}
};

int main(int argc, char **argv)
{
	glfwInit();
	testWindow t;
	w.ReadIn("rndtest");

//	for(unsigned int i = 0; i < w.Used; ++i)
//		std::cout << w[i][0] << "\t" << w[i][1] << std::endl;
	glClearColor(1, 1, 1, 1);
	while(t)
		t.Update();
	glfwTerminate();
	return 0;
}
