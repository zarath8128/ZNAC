#ifndef ZARATH_ZNAC_VISUALIZE_GLFW_JOYSTICK_H
#define ZARATH_ZNAC_VISUALIZE_GLFW_JOYSTICK_H

namespace ZNAC
{
	namespace Visualize
	{
		class Joystick
		{
		public:
			float * const &Axes = axes;
			const int &AxesRange = arange;
			unsigned char * const &Buttons = buttons;
			const int &ButtonsRange = brange;
			const char *Name;

			Joystick();
			Joystick(int joy);

			void Update();
			operator bool();

		private:
			int joy;
			int arange, brange;
			float *axes;
			unsigned char *buttons;
			bool isEnable;
		};
	}
}

#endif
