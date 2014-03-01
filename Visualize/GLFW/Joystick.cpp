#include "Joystick.h"
#include <GLFW/glfw3.h>

using namespace ZNAC::GLFW;

Joystick::Joystick()
	:Joystick(0){}

Joystick::Joystick(int joy)
	:joy(joy)
{
	isEnable = (glfwJoystickPresent(joy) == GL_TRUE);
}

const float *Joystick::Axes(int &range){return glfwGetJoystickAxes(joy, &range);}
const unsigned char *Joystick::Buttons(int &range){return glfwGetJoystickButtons(joy, &range);}
const char *Joystick::Name(){return glfwGetJoystickName(joy);}

Joystick::operator bool()
{
	return isEnable;
}
