#ifndef ZARATH_ZNAC_ODE_EULER_METHOD_H
#define ZARATH_ZNAC_ODE_EULER_METHOD_H

#include "ODE.h"

namespace ZNAC
{
	namespace ODE
	{
		class EulerMethod
			:public ODESolver
		{
		public:
			EulerMethod(Domain &x0, ODE &&f, double dt);
			~EulerMethod();
			void operator++();

		private:
			double dt;
		};
	}
}

#endif
