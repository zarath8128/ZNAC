#ifndef ZARATH_ZNAC_VISUALIZE_GLFW_JOYSTICK_H
#define ZARATH_ZNAC_VISUALIZE_GLFW_JOYSTICK_H

namespace ZNAC
{
	namespace GLFW
	{
		class Joystick
		{
		public:
			Joystick();
			Joystick(int joy);

			const float *Axes(int &range);
			const unsigned char *Buttons(int &range);
			const char *Name();

			operator bool();

		private:
			int joy;
			bool isEnable;
		};
	}
}

#endif
