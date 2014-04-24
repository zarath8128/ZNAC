#ifndef ZARATH_ZNAC_ODE_EULER_METHOD_H
#define ZARATH_ZNAC_ODE_EULER_METHOD_H

#include "ODE.h"

namespace ZNAC
{
	namespace ODE
	{
		template<class T>
		class EulerMethod
			:public ODESolver<T>
		{
		public:
			EulerMethod(unsigned int N):ODESolver<T>(N){};

			void operator()(const ODE<T> &f, const LA::IVector<T> &x0, LA::IVector<T> &x1, double dt)
			{
				f(x0, this->temp);
				for(unsigned int i = 0; i < this->N; ++i)
					x1[i] = x0[i] + dt*this->temp[i];
			}
		};
	}
}

#endif
