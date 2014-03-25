#ifndef ZARATH_ZNAC_ODE_RUNGE_KUTTA_FEHLBERG_METHOD_H
#define ZARATH_ZNAC_ODE_RUNGE_KUTTA_HEHLBERG_METHOD_H

#include "ODE.h"
#include "../LA/Norm.h"
#include <cmath>

namespace ZNAC
{
	namespace ODE
	{
		template<class T>
		class RKFMethod
			:public ODESolver<T>
		{
		public:
			RKFMethod(LA::Vector<T> &x0, double dt, double tol, const LA::INorm<T> &norm):ODESolver<T>(x0), tol(tol), h(dt), norm(norm.Clone())
			{
				for(unsigned int i = 0; i < 6; ++i)
					k[i] = x0.Clone();
				xtemp = x0.Clone();
				x1temp= x0.Clone();
			}
			~RKFMethod()
			{
				for(unsigned int i = 0; i < 6; ++i)
					delete k[i];
				delete xtemp;
				delete x1temp;
				delete norm;
			}

			void Setdt(double dt){h = dt;}

			double Step(ODE<T> &f, LA::Vector<T> &x0, LA::Vector<T> &x1, double t, double dt, bool fix = false)
			{
				double err = 0;
				double tmpdt;
				do
				{
					f(x0, *k[0]);
					for(unsigned int i = 0; i < x0.dim(); ++i)
						xtemp->operator[](i) = x0[i] + dt*0.25* (*k[0])[i];
					f(*xtemp, *k[1]);
					for(unsigned int i = 0; i < x0.dim(); ++i)
						xtemp->operator[](i) = x0[i] + dt*((3/32.)*(*k[0])[i] + (9/32.)*(*k[1])[i]);
					f(*xtemp, *k[2]);
					for(unsigned int i = 0; i < x0.dim(); ++i)
						xtemp->operator[](i) = x0[i] + dt*((1932/2197.)*(*k[0])[i] + (-7200/2197.)*(*k[1])[i] + (7296/2197.)*(*k[2])[i]);
					f(*xtemp, *k[3]);
					for(unsigned int i = 0; i < x0.dim(); ++i)
						xtemp->operator[](i) = x0[i] + dt*((439/216.)*(*k[0])[i] - 8*(*k[1])[i] + (3680/513.)*(*k[2])[i] + (-845/4104.)*(*k[3])[i]);
					f(*xtemp, *k[4]);
					for(unsigned int i = 0; i < x0.dim(); ++i)
						xtemp->operator[](i) = x0[i] + dt*((-8/27.)*(*k[0])[i] + 2*(*k[1])[i] - (3544/2565.)*(*k[2])[i] + (1859/4104.)*(*k[3])[i] - (11/40.)*(*k[4])[i]);
					f(*xtemp, *k[5]);

					for(unsigned int i = 0; i < x0.dim(); ++i)
					{
						xtemp->operator[](i) = x0[i] + dt*((25/216.)*(*k[0])[i] + (1408/2565.)*(*k[2])[i] + (2197/4104.)*(*k[3])[i] - (1/5.)*(*k[4])[i]);
						x1temp->operator[](i) = x0[i] + dt*((16/135.)*(*k[0])[i] + (6656/12825.)*(*k[2])[i] + (28561/56430.)*(*k[3])[i] - (9/50.)*(*k[4])[i] + (2/55.)*(*k[5])[i]);
					}

					for(unsigned int i = 0; i < x0.dim(); ++i)
						xtemp->operator[](i) = ((*x1temp)[i] != 0)?(ABS((x1temp->operator[](i) - xtemp->operator[](i))/x1temp->operator[](i))):(((*xtemp)[i] !=  0)?(ABS((x1temp->operator[](i) - xtemp->operator[](i))/x1temp->operator[](i))):(0));

					err = norm->operator()(*xtemp);

					tmpdt = dt;

					dt *= ((err != 0)?(0.9*pow(tol/err, 1/6.)):(2));

				}while((err > tol) && !fix);
				h = dt;
				for(unsigned int i = 0; i < x0.dim(); ++i)
					x1[i] = x1temp->operator[](i);
				return tmpdt;
			}

		protected:
			double tol;
			double h;
			LA::Vector<T> *k[6], *xtemp, *x1temp;
			LA::INorm<T> *norm;

			double dt(){return h;}
		};
	}
}

#endif
