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
	Vector<dim> v, w, b;
	Matrix<dim> m;

	for(unsigned int r = 0; r < dim; ++r)
		for(unsigned int c = 0; c < dim; ++c)
			m(r, c) = ((r == c)?(2.1):((r == c - 1 || r == c + 1)?(-1):(0)));

	for(unsigned int i = 0; i < dim; ++i)
	{
		b[i] = (rand() % 256)/255.;
		w[i] = 0;
		//for(unsigned int j = 0; j < dim; ++j)
		//	std::cout << m(i, j) << "\t";
		//std::cout << std::endl;
	}


	lNorm<double> l2(2);
	supNorm<double> linf;
	Jacobi<double> j(200000, 1e-12, l2);
	GaussSeidel<double> gs(200000, 1e-12, l2);
	CG<double> cg(dim, 1e-12, l2);

/*	clock_t t0 = clock();
	j(m, w, b);
	clock_t t1 = clock();
	m(w, v);

	for(unsigned int i = 0; i < dim; ++i)
		v[i] = ABS(v[i] - b[i]), w[i] = 0;

	double j_err = l2(v);

	clock_t t2 = clock();
	gs(m, w, b);
	clock_t t3 = clock();
	m(w, v);

	for(unsigned int i = 0; i < dim; ++i)
		v[i] = ABS(v[i] - b[i]);

	double gs_err = l2(v);

	m(w, v);

	for(unsigned int i = 0; i < v.dim(); ++i)
		std::cout << v[i] << " " << b[i] << std::endl;

	std::cout << "jaccobi:\t" << (t1 - t0)/(double)CLOCKS_PER_SEC << "\terr:\t" << j_err << std::endl;
	std::cout << "GS     :\t" << (t3 - t2)/(double)CLOCKS_PER_SEC << "\terr:\t" << gs_err << std::endl;
*/
	clock_t t4 = clock();
	cg(m, w, b);
	clock_t t5 = clock();

	m(w, v);

	for(unsigned int i = 0; i < dim; ++i)
		v[i] = ABS(v[i] - b[i]);

	double cg_err = l2(v);

	m(w, v);

	for(unsigned int i = 0; i < v.dim(); ++i)
		std::cout << v[i] << " " << b[i] << std::endl;

	std::cout << "CG     :\t" << (t5 - t4)/(double)CLOCKS_PER_SEC << "\terr:\t" << cg_err << std::endl;


	return 0;
}
