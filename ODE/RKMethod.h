#ifndef ZARATH_ZNAC_ODE_RUNGE_KUTTA_CLASICAL_H
#define ZARATH_ZNAC_ODE_RUNGE_KUTTA_CLASICAL_H

#include "ODE.h"

namespace ZNAC
{
	namespace ODE
	{
		class RKMethod
			:public ODESolver
		{
		public:
			RKMethod(Domain &x0, ODE &&f, double dt);
			~RKMethod();
			void operator++();

		private:
			double dt;
			Domain *k[4];
		};
	}
}

#endif
