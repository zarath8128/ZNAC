#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

#include "../LA/Vector.h"
#include "EulerMethod.h"
#include "RKMethod.h"
#include "Dahlquist.h"

using namespace ZNAC::ODE;
using namespace ZNAC::LA;

int main()
{
	constexpr unsigned int dim = 12;
	Vector<dim> x0, param, x;

	for(unsigned int i = 0; i < dim; ++i)
		x0[i] = 1, param[i] = -(i + 1.);

	double dt = 1e-6;
	EulerMethod<double> e(x, dt);
	RKMethod<double> rk(x, dt);
	Dahlquist<double> d(param);

	e(d, x0, x, 0, 1);

	for(unsigned int i = 0; i < dim; ++i)
		std::cout << x[i] << "\t" << x[i] - exp(param[i])<< "\n";

	std::cout << std::endl;

	rk(d, x0, x, 0, 1);

	for(unsigned int i = 0; i < dim; ++i)
		std::cout << x[i] << "\t" << x[i] - exp(param[i])<< "\n";
}
