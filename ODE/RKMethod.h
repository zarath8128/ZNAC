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
			RKMethod(LA::IVector<T> &x0, double dt):ODESolver<T>(x0), h(dt)
			{
				for(int i = 0; i < 4; ++i)
					k[i] = x0.Clone();
				xtemp = x0.Clone();
			}
			~RKMethod()
			{
				for(int i = 0; i < 4; ++i)
					delete k[i];
				delete xtemp;
			}

			void Setdt(double dt){h = dt;}

			double Step(ODE<T> &f, LA::IVector<T> &x0, LA::IVector<T> &x1, double t, double dt)
			{
				f(x0, *k[0]);
				for(unsigned int i = 0; i < x0.dim(); ++i)
					xtemp->operator[](i) = x0[i] + 0.5*dt*k[0]->operator[](i);
				f(*xtemp, *k[1]);
				for(unsigned int i = 0; i < x0.dim(); ++i)
					xtemp->operator[](i) = x0[i] + 0.5*dt*k[1]->operator[](i);
				f(*xtemp, *k[2]);
				for(unsigned int i = 0; i < x0.dim(); ++i)
					xtemp->operator[](i) = x0[i] + dt*k[2]->operator[](i);
				f(*xtemp, *k[3]);
				for(unsigned int i = 0; i < x0.dim(); ++i)
					x1[i] = x0[i] + dt*(k[0]->operator[](i)+2*k[1]->operator[](i)+2*k[2]->operator[](i)+k[3]->operator[](i))*(1/6.);
				return dt;
			}

		private:
			double h;
			LA::IVector<T> *k[4], *xtemp;

			double dt(){return h;}
		};
	}
}

#endif
