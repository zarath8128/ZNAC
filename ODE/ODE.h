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
		virtual void operator()(LA::Vector<T> &u, LA::Vector<T> &du) = 0;
	};

	template<class T>
	class ODESolver
	{
	public:
		ODESolver(LA::Vector<T> &x0):temp(x0.Clone()){}
		virtual ~ODESolver(){delete temp;}
		void operator()(ODE<T> &f, LA::Vector<T> &x0, LA::Vector<T> &x, double t_init, double t_term)
		{
			double t = t_init;
			for(unsigned int i = 0; i < x0.dim(); ++i)
				temp->operator[](i) = x0[i];
			while(t + dt() < t_term)
				t += Step(f, *temp, *temp, t, dt());

			t += Step(f, *temp, x, t, t_term - t, true);
		}

		virtual double Step(ODE<T> &f, LA::Vector<T> &x0, LA::Vector<T> &x1, double t, double dt, bool fix = false) = 0;

	protected:
		LA::Vector<T> *temp;

		virtual double dt() = 0;
	};

	}
}

#endif
