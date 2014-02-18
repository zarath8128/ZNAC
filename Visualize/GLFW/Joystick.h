#ifndef ZARATH_ZNAC_VISUALIZE_GLFW_JOYSTICK_H
#define ZARATH_ZNAC_VISUALIZE_GLFW_JOYSTICK_H

namespace ZNAC
{
	namespace GLFW
	{
		class Joystick
		{
		public:
			const char *name;
			const float *axes;
			int axes_range;
			const unsigned char *buttons;
			int buttons_range;

			

			Joystick();
			Joystick(int joy);

			void Update();

			operator bool();

		private:
			int joy;
		};
	}
}

#endif
