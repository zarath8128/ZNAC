#include <iostream>
#include "Diffusion2D.h"
#include "../ODE/RKMethod.h"
#include "../ODE/RKFMethod.h"

using namespace ZNAC::PDE;
using namespace ZNAC::ODE;

int main()
{
	constexpr unsigned int xdim = 16, ydim = 16;
	double width = 1;
	Field2D<double> v(2, xdim, ydim), w(2, xdim, ydim);
	FHN<double, Neumann2D, 1> d(v, width, width);
	//Diffusion2D<double, Neumann2D, 1> d(v, width, width);
	RKMethod<double> rk(v, 1e-6);
	RKFMethod<double> rkf(v, 1e-6, 1e-4, ZNAC::LA::supNorm<double>());

	for(unsigned int i = 0; i < ydim; ++i)
		for(unsigned int j = 0; j < xdim; ++j)
			v(0, i, j) = ((j < 3)?(0.22):(0)), v(1, i, j) = 0;

	for(unsigned int i = 0; i < ydim; ++i)
	{
		for(unsigned int j = 0; j < xdim; ++j)
			std::cout << v(0, i, j) << "\t";
		std::cout << "\n";
	}

	std::cout << std::endl;

	for(unsigned int i = 0; i < ydim; ++i)
	{
		for(unsigned int j = 0; j < xdim; ++j)
			std::cout << v(1, i, j) << "\t";
		std::cout << "\n";
	}

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	
	//d(v, w);
	rkf(d, v, w, 0, .1);

	for(unsigned int i = 0; i < ydim; ++i)
	{
		for(unsigned int j = 0; j < xdim; ++j)
			std::cout << w(0, i, j) << "\t";
		std::cout << "\n";
	}

	std::cout << std::endl;

	for(unsigned int i = 0; i < ydim; ++i)
	{
		for(unsigned int j = 0; j < xdim; ++j)
			std::cout << w(1, i, j) << "\t";
		std::cout << "\n";
	}
}
