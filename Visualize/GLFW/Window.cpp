#include "Window.h"
#include "../OpenGL/GLUtility.h"
#include <iostream>
#include <cstdlib>

using namespace ZNAC::Visualize;

unsigned int Window::wnd_nums = 0;
int Window::context_major = 0;
int Window::context_minor = 0;

void glfw_error_func(int err, const char* message)
{
	std::cerr << "\n------------ GLFW ERROR! ------------\n\n";
	std::cerr << "error code:" << std::hex << err << "\n";
	std::cerr << message << "\n";
	std::cerr << "\n-------------------------------------\n";
}

namespace ZNAC
{
	namespace Visualize
	{
		void glfw_wnd_pos_func(GLFWwindow *wnd, int x, int y)
		{
			Window *w = (Window*)glfwGetWindowUserPointer(wnd);
			w->x = x;
			w->y = y;
		}
		void glfw_wnd_size_func(GLFWwindow *wnd, int width, int height)
		{
			Window *w = (Window*)glfwGetWindowUserPointer(wnd);
			w->width = width;
			w->height = height;
		}
		void glfw_wnd_fbsize_func(GLFWwindow *wnd, int width, int height)
		{
			Window *w = (Window*)glfwGetWindowUserPointer(wnd);
			w->fbwidth = width;
			w->fbheight = height;
		}
	}
}

static const char default_wnd_title[] = "ZNAC Window using GLFW3";

Window::Window():Window(640, 480, 100, 100, default_wnd_title){}
Window::Window(bool IsFullScreen)
	:Window(640, 480, 100, 100, default_wnd_title, IsFullScreen){}

Window::Window(const char* title, bool IsVisible):Window(640, 480, 100, 100, title, IsVisible){}
Window::Window(int width, int height, bool IsVisible):Window(width, height, 100, 100, default_wnd_title, IsVisible){}
Window::Window(int width, int height, const char *title, bool IsVisible):Window(width, height, 100, 100, title, IsVisible){}
Window::Window(int width, int height, int x, int y, bool IsVisible):Window(width, height, x, y, default_wnd_title, IsVisible){}
Window::Window(int width, int height, int x, int y, const char *title, bool IsVisible):Window(width, height, x, y, title, false, IsVisible){}
Window::Window(int width, int height, int x, int y, const char *title, bool isFullScreen, bool IsVisible)
	:Width(this->width), Height(this->height), X(this->x), Y(this->y), fbWidth(this->fbwidth), fbHeight(fbheight), wnd(0), width(width), height(height), x(x), y(y)
{
	if(!wnd_nums++)
	{
		GLFWerrorfun errfun = glfwSetErrorCallback(nullptr);
		glfwSetErrorCallback(errfun == nullptr?glfw_error_func:errfun);
		if(glfwInit() == GL_TRUE)
			std::cerr << "GLFW library Initialized\n";
		else
		{
			std::cerr << "Initializing GLFW library is failed\n";
			return;
		}
	}

	if(isFullScreen)
	{
		std::cerr << "FullScreen Window\n";

		int count;
		const GLFWvidmode *modes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
		int maxw = 0, maxh = 0;

		for(int i = 0; i < count; ++i)
			if(modes[i].width >= maxw && modes[i].height > maxh)
				maxw = modes[i].width, maxh = modes[i].height;
		width = maxw;
		height = maxh;
		std::cerr << "width:\t" << width << "\n";
		std::cerr << "height:\t" << height << "\n";
	}
	
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_VISIBLE, IsVisible?GL_TRUE:GL_FALSE);

	wnd = glfwCreateWindow(width, height, title, ((isFullScreen)?(glfwGetPrimaryMonitor()):(nullptr)), nullptr);

	if(!wnd)
	{
		std::cerr << "Failed window creation\t:message will be upon" << std::endl;
		return;
	}

	glfwSetWindowUserPointer(wnd, this);

	glfwSetWindowPosCallback(wnd, glfw_wnd_pos_func);
	glfwSetWindowSizeCallback(wnd, glfw_wnd_size_func);
	glfwSetFramebufferSizeCallback(wnd, glfw_wnd_fbsize_func);

	if(!isFullScreen)
		glfwSetWindowPos(wnd, x, y);

	glfwMakeContextCurrent(wnd);

	glfwGetFramebufferSize(wnd, &fbwidth, &fbheight);
	glfwGetWindowSize(wnd, &width, &height);
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

Window::operator bool(){return wnd && !glfwWindowShouldClose(wnd);}
Window::operator GLFWwindow*(){return wnd;}

void Window::Update()
{
	glfwPollEvents();
	if(glfwGetKey(wnd, GLFW_KEY_ESCAPE) != GLFW_RELEASE || glfwGetKey(wnd, GLFW_KEY_Q) != GLFW_RELEASE)
		glfwSetWindowShouldClose(wnd, 1);
}
