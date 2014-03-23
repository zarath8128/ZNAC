#include <iostream>
#include <GL/gl.h>
#include "../basic/general.h"
#include "GLFW/Window.h"
#include "GLUtility.h"

using namespace ZNAC;
using namespace Visualize;

int main()
{
	glfwInit();
	GLFW::Window w;
	SetErrorCallback();
	glEnd();
	std::cout << std::hex << CheckError() << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
	return 0;
}
