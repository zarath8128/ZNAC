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
			EulerMethod(LA::IVector<T> &x0, double dt):ODESolver<T>(x0),h(dt), xtemp(x0.Clone()){};
			~EulerMethod(){delete xtemp;};
			
			void Setdt(double dt){h = dt;}

			double Step(ODE<T> &f, LA::IVector<T> &x0, LA::IVector<T> &x1, double t, double dt)
			{
				f(x0, *xtemp);
				for(unsigned int i = 0; i < xtemp->dim(); ++i)
					x1[i] = x0[i] + dt*xtemp->operator[](i);
				return dt;
			}

		private:
			double h;
			LA::IVector<T> *xtemp;

			double dt(){return h;}
		};
	}
}

#endif
