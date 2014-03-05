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
			EulerMethod(unsigned int dim):ODESolver<T>(dim), xtemp(new T[dim]){};
			~EulerMethod(){delete xtemp;};
			
			void Setdt(double dt){this->dt = dt;}

			double Step(ODE<T> &f, T *x0, T *x1, double &dt)
			{
				f(x0, xtemp);
				for(unsigned int i = 0; i < this->dim; ++i)
					x1[i] = x0[i] + dt*xtemp[i];
				return dt;
			}

		private:
			T *xtemp;
		};
	}
}

#endif
