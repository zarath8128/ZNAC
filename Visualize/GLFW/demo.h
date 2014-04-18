#include "Window.h"
#include "Camera.h"
#include "Joystick.h"

namespace ZNAC
{
	namespace Visualize
	{
		namespace GLFW
		{
			class demoWindow
				:public Window
			{
			public:


				demoWindow();
			protected:
				void update();

				Camera c;
				Joystick j;
			};
		}
	}
}
