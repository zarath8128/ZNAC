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
			const unsigned int N;

			ODE(unsigned int N):N(N){}
			virtual void operator()(const LA::IVector<T> &u, LA::IVector<T> &du) const = 0;
		};

		template<class T>
		class ODESolver
		{
		public:
			ODESolver(unsigned int N):N(N), temp(N){}
			virtual ~ODESolver(){}

			virtual void operator()(const ODE<T> &f, const LA::IVector<T> &x0, LA::IVector<T> &x1, double dt) = 0;

		protected:
			const unsigned int N;
			LA::Vector<T> temp;
		};

	}
}

#endif
