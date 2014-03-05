#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "EulerMethod.h"
#include "RKMethod.h"

using namespace ZNAC;
using namespace ODE;


int main()
{
	EulerMethod<double> eu(20);
	RKMethod<double> rk(20);
}
