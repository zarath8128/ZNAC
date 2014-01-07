#include "RKMethod.h"

using namespace ZNAC::ODE;

RKMethod::RKMethod(Domain &x0, ODE &&f, double dt):ODESolver(x0, f), dt(dt)
{
	for(unsigned int i = 0; i < 4; ++i)
		k[i] = x0.Clone();
}

RKMethod::~RKMethod()
{
	for(unsigned int i = 0; i < 4; ++i)
		delete k[i];
}

void RKMethod::operator++()
{
	f(*x, *k[0]);

	for(unsigned int i = 0; i < x->Range(); ++i)
		(*temp)[i] = (*x)[i] + 0.5*dt*(*k[0])[i];
	f(*temp, *k[1]);

	for(unsigned int i = 0; i < x->Range(); ++i)
		(*temp)[i] = (*x)[i] + 0.5*dt*(*k[1])[i];
	f(*temp, *k[2]);

	for(unsigned int i = 0; i < x->Range(); ++i)
		(*temp)[i] = (*x)[i] + dt*(*k[2])[i];
	f(*temp, *k[3]);

	for(unsigned int i = 0; i < x->Range(); ++i)
		(*x)[i] += (1./6)*dt*((*k[0])[i] + 2*(*k[1])[i] + 2*(*k[2])[i] + (*k[3])[i]);
}
