#ifndef ZARATH_ZNAC_LA_LEQ_SOLVER_H
#define ZARATH_ZNAC_LA_LEQ_SOLVER_H

#include "Matrix.h"
#include "Norm.h"

namespace ZNAC
{
	namespace LA
	{
		template<class T>
		T &MAX(T &a, T &b){return ((a < b)?(b):(a));}

		template<class T>
		T ABS(T &x){return ((x < 0)?(-x):(x));}

		template<class T>
		class LEQSolver
		{
		public:
			virtual void operator()(absMatrix<T> &m, absVector<T> &x, absVector<T> &b) = 0;
		};

		template<class T>
		class Jacobi
			:public LEQSolver<T>
		{
		public:
			constexpr Jacobi(unsigned int limit, double eps, absNorm<T> &norm):lim(limit), eps(eps), norm(norm.Clone()){}
			~Jacobi(){delete norm;}
			void operator()(absMatrix<T> &m, absVector<T> &x, absVector<T> &b)
			{
				absVector<T> *tmp = b.Clone();
				T t;
				for(unsigned int i = 0; i < lim; ++i)
				{
					for(unsigned int r = 0; r < b.dim(); ++r)
					{
						tmp->operator[](r) = b[r];
						for(unsigned int c = 0; c < r; ++c)
							tmp->operator[](r) -= m(r, c)*x[c];
						for(unsigned int c = r + 1; c < b.dim(); ++c)
							tmp->operator[](r) -= m(r, c)*x[c];
						tmp->operator[](r) /= m(r, r);
					}

					for(unsigned int r = 0; r < b.dim(); ++r)
						t = tmp->operator[](r) - x[r], x[r] = tmp->operator[](r), tmp->operator[](r) = ABS(t);

					if(norm->operator()(*tmp) < eps)
						break;
				}

				delete tmp;
			}

		private:
			unsigned int lim;
			double eps;
			absNorm<T> *norm;
		};
	}
}

#endif
