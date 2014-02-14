#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "LEQSolver.h"

using namespace ZNAC::LA;

template<class T>
void te(absVector<T> &g)
{
	std::cout << g[0] << std::endl;
}


int main()
{
	constexpr unsigned int dim = 2000;
	Vector<dim> v, w, b;
	Matrix<dim> m;
	v[3] = 0.8;

	for(unsigned int r = 0; r < dim; ++r)
		for(unsigned int c = 0; c < dim; ++c)
			m(r, c) = ((r == c)?(300.1):(-1./dim));

	for(unsigned int i = 0; i < dim; ++i)
	{
		b[i] = 0.03223223213;
		//for(unsigned int j = 0; j < dim; ++j)
		//	std::cout << m(i, j) << "\t";
		//std::cout << std::endl;
	}


	lNorm<double> l2(2);
	Jacobi<double> j(200, 1e-12, l2);
	j(m, w, b);

	m(w, v);

	for(unsigned int i = 0; i < v.dim(); ++i)
		std::cout << v[i] << " " << b[i] << std::endl;
	return 0;
}
