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
			RKMethod(unsigned int N):ODESolver<T>(N), xtemp(new T[4*N]), k1(N, xtemp), k2(N, xtemp + N), k3(N, xtemp + 2*N), k4(N, xtemp + 3*N){}
			~RKMethod(){delete [] xtemp;}

			void operator()(const ODE<T> &f, const LA::IVector<T> &x0, LA::IVector<T> &x1, double dt)
			{
				f(x0, k1);
				for(unsigned int i = 0; i < this->N; ++i)
					this->temp[i] = x0[i] + 0.5*dt*k1[i];
				f(this->temp, k2);
				for(unsigned int i = 0; i < this->N; ++i)
					this->temp[i] = x0[i] + 0.5*dt*k2[i];
				f(this->temp, k3);
				for(unsigned int i = 0; i < this->N; ++i)
					this->temp[i] = x0[i] + dt*k3[i];
				f(this->temp, k4);
				for(unsigned int i = 0; i < this->N; ++i)
					x1[i] = x0[i] + dt*(k1[i] + 2*k2[i] + 2*k3[i] + k4[i])*(1/6.);
			}

		private:
			T *xtemp;
			LA::WrapVector<T> k1, k2, k3, k4;
		};
	}
}

#endif
