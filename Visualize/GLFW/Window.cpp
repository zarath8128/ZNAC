#include "Window.h"
#include <iostream>

using namespace ZNAC::GLFW;

Window::Window():Window(640, 480, "ZNAC Window based on GLFW3"){}
Window::Window(unsigned int width, unsigned int height, const char *title, bool isFullScreen)
	:wnd(glfwCreateWindow(width, height, title, ((isFullScreen)?(glfwGetPrimaryMonitor()):(0)), 0)), shouldClose(false)
{
	if(!wnd)
	{
		std::cerr << "failed create window" << std::endl;
		return;
	}

	glfwMakeContextCurrent(wnd);
}

Window::~Window()
{
	glfwDestroyWindow(wnd);
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
