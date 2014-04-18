#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Vector.h"
#include "Matrix.h"
#include "LEQSolver.h"
#include <ctime>

using namespace ZNAC::LA;



int main()
{
	constexpr unsigned int d = 5000;
	GaussMatrix<double> G(d);
	//Matrix<double> G(d);
	LUMatrix<double> L(d);
	Vector<double> v(d), w(d);

	for(unsigned int i = 0; i < d; ++i)
		for(unsigned int j = 0; j < d; ++j)
			G(i, j) = 1./(i + j + 1);

	for(unsigned int i = 0; i < d; ++i)
		w[i] = 1.;///(1 + i);

	/*for(unsigned int i = 0; i < d; ++i)
	{
		for(unsigned int j = 0; j < d; ++j)
			std::cout << "\t" << G(i, j);
		std::cout << std::endl;
	}

	L << G;

	std::cout << std::endl;

	if(L)
	for(unsigned int i = 0; i < d; ++i)
	{
		for(unsigned int j = 0; j < d; ++j)
			std::cout << "\t" << L(i, j);
		std::cout << std::endl;
	}*/
	
	clock_t t0 = clock();
	//Gauss<double>()(G, v, w);
	LUSolver<double>()(G, v, w);
	clock_t t1 = clock();
	
	for(unsigned int i = 0; i < d; ++i)
		std::cout << v[i] << std::endl;

	G(v, w);
	
	
	for(unsigned int i = 0; i < d; ++i)
		std::cout << w[i] << std::endl;
	std::cout << "time:" << (t1 - t0)/(double)CLOCKS_PER_SEC << std::endl;

	return 0;
}
