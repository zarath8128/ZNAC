#include <GL/gl.h>
#include <iostream>
#include "../Window/Window.h"
#include "GLUtility.h"

using namespace ZNAC::Visualize;
using namespace OpenGL;

int main()
{
	ZNAC::Visualize::Window w;
	Version v;
	std::cout << v.Major << std::endl;
	std::cout << v.Minor << std::endl;
	return 0;
}
