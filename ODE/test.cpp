#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "EulerMethod.h"
#include "RKMethod.h"
#include "Dahlquist.h"

using namespace ZNAC;
using namespace ODE;
using namespace LA;

int main()
{
	EulerMethod<double> eu(20);
	RKMethod<double> rk(20);
	LA::Vector<int> v = {1, 2, 3, 4, 5};

	for(int i = 0; i < v; ++i)
		std::cout << v[i] << std::endl;
}
