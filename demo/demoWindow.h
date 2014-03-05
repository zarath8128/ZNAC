#include "../Visualize/GLFW/Window.h"
#include "../Visualize/GLFW/Camera.h"
#include "../Visualize/GLFW/Joystick.h"
#include "../PDE/Diffusion2D.h"
#include "../ODE/RKFMethod.h"

namespace ZNAC
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

		private:
			Camera c;
			Joystick j;
			PDE::Field2D<double> F;
			PDE::FHN<double, PDE::Neumann2D, 1> D;
			ODE::RKFMethod<double> rk;
		};
	}
}
