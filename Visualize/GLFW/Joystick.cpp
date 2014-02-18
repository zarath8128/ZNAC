#include "Joystick.h"
#include <GLFW/glfw3.h>

using namespace ZNAC::GLFW;

Joystick::Joystick()
	:Joystick(0){}

Joystick::Joystick(int joy)
	:joy(joy)
{
	if(glfwJoystickPresent(joy) == GL_TRUE)
		name = glfwGetJoystickName(joy);
	else
		name = 0;

	if(*this)
		Update();
}

void Joystick::Update()
{
	axes = glfwGetJoystickAxes(joy, &axes_range);
	buttons = glfwGetJoystickButtons(joy, &buttons_range);
}

Joystick::operator bool()
{
	return name != 0;
}
