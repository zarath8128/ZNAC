#ifndef ZARATH_ZNAC_ODE_RUNGE_KUTTA_CLASICAL_H
#define ZARATH_ZNAC_ODE_RUNGE_KUTTA_CLASICAL_H

#include "ODE.h"

namespace ZNAC
{
	namespace ODE
	{
		template<class T>
		class RKMethod
			:public ODESolver<T>
		{
		public:
			RKMethod(unsigned int dim):ODESolver<T>(dim), xtemp(new T[5*dim])
			{
				for(unsigned int i = 0; i < 4; ++i)
					k[i] = xtemp + dim*(i + 1);
			}
			~RKMethod(){delete xtemp;}

			double Step(ODE<T> &f, T *x0, T *x1, double &dt)
			{
				f(x0, k[0]);
				for(unsigned int i = 0; i < this->dim; ++i)
					xtemp[i] = x0[i] + 0.5*dt*k[0][i];
				f(xtemp, k[1]);
				for(unsigned int i = 0; i < this->dim; ++i)
					xtemp[i] = x0[i] + 0.5*dt*k[1][i];
				f(xtemp, k[2]);
				for(unsigned int i = 0; i < this->dim; ++i)
					xtemp[i] = x0[i] + dt*k[2][i];
				f(xtemp, k[3]);
				for(unsigned int i = 0; i < this->dim; ++i)
					x1[i] = x0[i] + dt*(k[0][i] + 2*k[1][i] + 2*k[2][i] + k[3][i])*(1/6.);
				return dt;
			}

		private:
			T *k[4], *xtemp;
		};
	}
}

#endif
