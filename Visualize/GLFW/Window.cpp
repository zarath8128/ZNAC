#include "Window.h"
#include <iostream>

using namespace ZNAC::Visualize::GLFW;

unsigned int Window::wnd_nums = 0;

void glfw_error_func(int err, const char* message)
{
	std::cerr << "\n------------ GLFW ERROR! ------------\n\n";
	std::cerr << "error code:" << std::hex << err << "\n";
	std::cerr << message << "\n";
	std::cerr << "\n-------------------------------------\n";
}

Window::Window():Window(640, 480, "ZNAC Window based on GLFW3"){}
Window::Window(unsigned int width, unsigned int height, const char *title, bool isFullScreen)
	:wnd(0), shouldClose(false)
{
	if(!wnd_nums++)
	{
		glfwSetErrorCallback(glfw_error_func);
		glfwInit();
		std::cerr << "GLFW library Initialized\n";
	}
	
	wnd = glfwCreateWindow(width, height, title, ((isFullScreen)?(glfwGetPrimaryMonitor()):(0)), 0);

	if(!wnd)
	{
		std::cerr << "Failed window creation\t:message will be upon" << std::endl;
		return;
	}

	glfwMakeContextCurrent(wnd);
}

Window::~Window()
{
	glfwDestroyWindow(wnd);
	if(!--wnd_nums)
	{
		glfwTerminate();
		std::cerr << "GLFW library Terminated\n";
	}
}

Window::operator bool(){return wnd && !shouldClose && !glfwWindowShouldClose(wnd);}
Window::operator GLFWwindow*(){return wnd;}

void Window::Update()
{
	glfwPollEvents();
	update();
	shouldClose = glfwGetKey(wnd, GLFW_KEY_ESCAPE) != GLFW_RELEASE || glfwGetKey(wnd, GLFW_KEY_Q) != GLFW_RELEASE;
}

void Window::update()
{
}
