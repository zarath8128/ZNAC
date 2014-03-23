#include "Screen.h"
#include "GLUtility.h"

using namespace ZNAC::Visualize;

Screen::Screen()
	:color(0), depth(0)
{
	SetErrorCallback();
	//glGenFramebuffersEXT(1, &color);
	//glGenFramebuffers(1, depth);
}
