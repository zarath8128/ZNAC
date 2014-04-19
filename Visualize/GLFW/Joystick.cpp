#include "Joystick.h"
#include <GLFW/glfw3.h>

using namespace ZNAC::Visualize;

Joystick::Joystick()
	:Joystick(0){}

Joystick::Joystick(int joy)
	:joy(joy), arange(0), brange(0), axes(nullptr), buttons(nullptr), isEnable(false)
{
	if((isEnable = (glfwJoystickPresent(joy) == GL_TRUE)))
	{
		const float *tmp = glfwGetJoystickAxes(joy, &arange);
		axes = new float[arange];
		for(int i = 0; i < arange; ++i)
			axes[i] = tmp[i];

		const unsigned char *btmp = glfwGetJoystickButtons(joy, &brange);
		buttons = new unsigned char[brange];
		for(int i = 0; i < brange; ++i)
			buttons[i] = btmp[i];

		Name = glfwGetJoystickName(joy);
	}
}

void Joystick::Update()
{
	int tmp;
	const float *atmp = glfwGetJoystickAxes(joy, &tmp);
	if(tmp != arange)
	{	
		delete [] axes;
		axes = new float[tmp];
		arange = tmp;
	}
	for(int i = 0; i < arange; ++i)
		axes[i] = atmp[i];

	const unsigned char *btmp = glfwGetJoystickButtons(joy, &tmp);
	if(tmp != brange)
	{	
		delete [] buttons;
		buttons = new unsigned char[tmp];
		brange = tmp;
	}
	for(int i = 0; i < brange; ++i)
		buttons[i] = btmp[i];
}

//const float *Joystick::Axes(int &range){return glfwGetJoystickAxes(joy, &range);}
//const unsigned char *Joystick::Buttons(int &range){return glfwGetJoystickButtons(joy, &range);}
//const char *Joystick::Name(){return glfwGetJoystickName(joy);}

Joystick::operator bool()
{
	return isEnable;
}
