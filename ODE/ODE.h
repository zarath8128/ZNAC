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
		virtual void operator()(T *u, T *du) = 0;
	};

	template<class T>
	class ODESolver
	{
	public:
		ODESolver(unsigned int dim):dim(dim), temp(new T[dim]){}
		virtual ~ODESolver(){delete temp;}
		void operator()(ODE<T> &f, T *x0, T *x, double t, double dt)
		{
			for(unsigned int i = 0; i < dim; ++i)
				temp[i] = x0[i];
			while(dt < t)
				t -= Step(f, temp, temp, dt);

			FixedStep(f, temp, x, t);
		}

		virtual double Step(ODE<T> &f, T *x0, T *x1, double &dt) = 0;
		virtual double FixedStep(ODE<T> &f, T *x0, T *x1, double dt){return Step(f, x0, x1, dt);}

	protected:
		const unsigned int dim;
		T *temp;
	};

	}
}

#endif
