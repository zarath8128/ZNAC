#include "EulerMethod.h"

#include <iostream>
using namespace ZNAC::ODE;

EulerMethod::EulerMethod(Domain &x0, ODE &&f, double dt):ODESolver(x0, f), dt(dt){}

EulerMethod::~EulerMethod(){}

void EulerMethod::operator++()
{
	f(*x, *temp);
	for(unsigned int i = 0; i < x->Range(); ++i)
		(*x)[i] += dt*(*temp)[i];
}
