#include <GLFW/glfw3.h>
#include <iostream>
#include "Window.h"
#include "demo.h"
#include "Joystick.h"

using namespace ZNAC;
using namespace GLFW;

int main()
{
	//glfwInit();
	//demoWindow wnd;
	Window wnd;
	while(wnd)
	{
		wnd.Update();
	}
}
