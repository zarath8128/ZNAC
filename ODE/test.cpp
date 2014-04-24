#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "EulerMethod.h"
#include "RKMethod.h"
#include "Dahlquist.h"

using namespace ZNAC;
using namespace ODE;
using namespace LA;

void printv(unsigned int n, double *var)
{
	for(unsigned int i = 0; i < n; ++i)
		std::cout << var[i] << std::endl;
}

int main()
{
	EulerMethod<double> eu(20);
	RKMethod<double> rk(20);
	LA::Vector<double> v(2, 3);

	double a[] = {1, 2, 3};

	printv(3, a);
}
