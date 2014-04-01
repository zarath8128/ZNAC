#include <iostream>
#include <random>
#include "Visualize/GLFW/Window.h"
#include "DelaunayTriangulation.h"

using namespace ZNAC::GLFW;

class testwnd
	:public Window
{
public:
	testwnd():Window()
	{
		glClearColor(1, 1, 1, 1);
	}

private:
	void update()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

		glfwSwapBuffers(wnd);
	}
};

int main()
{
	testwnd w;
	while(w)
		w.Update();
	return 0;
}
