#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Vector.h"
#include "Matrix.h"
#include "LEQSolver.h"

using namespace ZNAC::LA;

int main()
{
	constexpr unsigned int dim = 2;
	Vector<> v(dim), w(dim);
	double *b = new double[dim];
	Matrix<dim> m;
//	DiagonalMatrix<dim, 2> m;

	for(unsigned int r = 0; r < dim; ++r)
		for(unsigned int c = 0; c < dim; ++c)
			m(r, c) = ((r == c)?(4.1):(((int)(r - c) >= - 2 || (int)(r - c) <= 2)?(-1):(0)));

	for(unsigned int i = 0; i < dim; ++i)
	{
		b[i] = (rand() % 256)/255.;
		w[i] = 0;
//		for(unsigned int j = 0; j < dim; ++j)
//			std::cout << m(i, j) << "\t";
//		std::cout << std::endl;
	}

	lNorm<double> l2(dim, 2);
	std::cout << 2 << std::endl;
	l2.Set(b);
	std::cout << 2 << std::endl;

	std::cout << (double)l2 << std::endl;

	return 0;
}
