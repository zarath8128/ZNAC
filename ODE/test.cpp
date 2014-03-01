#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

#include "../LA/Vector.h"
#include "EulerMethod.h"
#include "RKMethod.h"
#include "Dahlquist.h"
#include "RKFMethod.h"

using namespace ZNAC::ODE;
using namespace ZNAC::LA;

int main()
{
	constexpr unsigned int dim = 12;
	Vector<double> x0(dim), param(dim), x(dim);

	for(unsigned int i = 0; i < dim; ++i)
		x0[i] = 1, param[i] = -25*(i + 1.);

	double dt = 1e-2;
	EulerMethod<double> e(x, dt);
	RKMethod<double> rk(x, dt);
	RKFMethod<double> rkf(x, dt, 1e-16, supNorm<double>());
	Dahlquist<double> d(param);

	std::cout << 123 << std::endl;
	e(d, x0, x, 0, 1);

	for(unsigned int i = 0; i < dim; ++i)
		std::cout << x[i] << "\t" << x[i] - exp(param[i])<< "\n";

	std::cout << std::endl;

	rk(d, x0, x, 0, 1);

	for(unsigned int i = 0; i < dim; ++i)
		std::cout << x[i] << "\t" << x[i] - exp(param[i])<< "\n";

	std::cout << std::endl;

	rkf(d, x0, x, 0, 1);

	for(unsigned int i = 0; i < dim; ++i)
		std::cout << x[i] << "\t" << x[i] - exp(param[i])<< "\t" << (x[i] - exp(param[i]))/exp(param[i])<< "\n";
}
