#include "demoWindow.h"

using namespace ZNAC::GLFW;

int main()
{
	glfwInit();

	demoWindow d;

	while(d)
		d.Update();

	glfwTerminate();
}
