#ifndef ZARATH_ZNAC_ODE_ODE_H
#define ZARATH_ZNAC_ODE_ODE_H
#include <iostream>

namespace ZNAC
{
	namespace ODE
	{

	class Domain
	{
	public:
		virtual unsigned int Range() = 0;
		virtual Domain *Clone() = 0;
		virtual double &operator[](unsigned int i) = 0;
	};

	class ODE
	{
	public:
		virtual void operator()(Domain &u, Domain &du) = 0;
	};

	class ODESolver
	{
	public:
		ODESolver(Domain &x0, ODE &&f):x(x0.Clone()), temp(x0.Clone()), f(f)
		{
			for(unsigned int i = 0; i < x0.Range(); ++i)
				(*x)[i] = x0[i];
		}
		virtual ~ODESolver(){delete x; delete temp;}
		virtual void operator++() = 0;
		void operator+(unsigned int count){for(unsigned int i = 0; i < count; ++i)++(*this);}
		virtual void operator>>(Domain &target)
		{
			for(unsigned int i = 0; i < x->Range(); ++i)
				target[i] = (*x)[i];
		}
	protected:
		Domain *x, *temp;
		ODE &f;
	};

	}
}

#endif
