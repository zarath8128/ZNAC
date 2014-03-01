#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Vector.h"
#include "Matrix.h"
#include "LEQSolver.h"

using namespace ZNAC::LA;

int main()
{
	constexpr unsigned int dim = 5000;
	Vector<> v(dim), w(dim), b(dim);
	Matrix<dim> m;
//	DiagonalMatrix<dim, 2> m;

	for(unsigned int r = 0; r < dim; ++r)
		for(unsigned int c = 0; c < dim; ++c)
			m(r, c) = ((r == c)?(4.1):((r - c >= - 2 || r - c <= 2)?(-1):(0)));

	for(unsigned int i = 0; i < dim; ++i)
	{
		b[i] = (rand() % 256)/255.;
		w[i] = 0;
//		for(unsigned int j = 0; j < dim; ++j)
//			std::cout << m(i, j) << "\t";
//		std::cout << std::endl;
	}

	lNorm<double> l2(2);
	CG<double> cg(dim, 1e-12, l2);

	clock_t t0 = clock();
	cg(m, w, b);
	clock_t t1 = clock();

	m(w, v);

//	for(unsigned int i = 0; i < dim; ++i)
//		std::cout << v[i] << "\t" << b[i] << std::endl;

	for(unsigned int i = 0; i < dim; ++i)
		v[i] -= b[i];

	std::cout << "time = " << (t1 - t0)/(double)CLOCKS_PER_SEC << std::endl;
	std::cout << "err  = " << l2(v) << std::endl;

	return 0;
}
