#ifndef ZARATH_ZNAC_ODE_ODE_H
#define ZARATH_ZNAC_ODE_ODE_H

#include "../basic/general.h"
#include "../LA/Vector.h"
#include <iostream>

namespace ZNAC
{
	namespace ODE
	{

	template<class T>
	class ODE
	{
	public:
		virtual void operator()(LA::IVector<T> &u, LA::IVector<T> &du) = 0;
	};

	template<class T>
	class ODESolver
	{
	public:
		ODESolver(LA::IVector<T> &x0):temp(x0.Clone()){}
		virtual ~ODESolver(){delete temp;}
		void operator()(ODE<T> &f, LA::IVector<T> &x0, LA::IVector<T> &x, double t_init, double t_term)
		{
			double t = t_init;
			double h = dt();
			for(unsigned int i = 0; i < x0.dim(); ++i)
				temp->operator[](i) = x0[i];
			while(t + h < t_term)
				t += Step(f, *temp, *temp, t, h);

			Step(f, *temp, x, t, t_term - t);
		}

		virtual double Step(ODE<T> &f, LA::IVector<T> &x0, LA::IVector<T> &x1, double t, double dt) = 0;

	protected:
		LA::IVector<T> *temp;

		virtual double dt() = 0;
	};

	}
}

#endif
