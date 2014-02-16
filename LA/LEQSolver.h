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
		T ABS(T x){return ((x < 0)?(-x):(x));}

		template<class T>
		class LEQSolver
		{
		public:
			virtual void operator()(IMatrix<T> &m, IVector<T> &x, IVector<T> &b) = 0;
		};

		template<class T>
		class Jacobi
			:public LEQSolver<T>
		{
		public:
			constexpr Jacobi(unsigned int limit, double eps, INorm<T> &norm):lim(limit), eps(eps), norm(norm.Clone()){}
			~Jacobi(){delete norm;}
			void operator()(IMatrix<T> &m, IVector<T> &x, IVector<T> &b)
			{
				IVector<T> *tmp = b.Clone();
				T t;
				for(unsigned int i = 0; i < lim; ++i)
				{
					for(unsigned int r = 0; r < b.dim(); ++r)
					{
						tmp->operator[](r) = b[r];
						for(unsigned int c = 0; c < b.dim(); ++c)
							tmp->operator[](r) -= m(r, c)*x[c];
						tmp->operator[](r) /= m(r, r);
						tmp->operator[](r) += x[r];
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
			INorm<T> *norm;
		};

		template<class T>
		class GaussSeidel
			:public LEQSolver<T>
		{
		public:
			constexpr GaussSeidel(unsigned int limit, double eps, INorm<T> &norm):lim(limit), eps(eps), norm(norm.Clone()){}
			~GaussSeidel(){delete norm;}
			void operator()(IMatrix<T> &m, IVector<T> &x, IVector<T> &b)
			{
				IVector<T> *tmp = b.Clone();
				T t;
				for(unsigned int i = 0; i < lim; ++i)
				{
					for(unsigned int r = 0; r < b.dim(); ++r)
					{
						tmp->operator[](r) = x[r];
						x[r] = b[r];
						for(unsigned int c = 0; c < r; ++c)
							x[r] -= m(r, c)*x[c];
						x[r] /= m(r, r);
						x[r] += tmp->operator[](r);
					}

					for(unsigned int r = 0; r < b.dim(); ++r)
						t = tmp->operator[](r) - x[r], tmp->operator[](r) = ABS(t);

					if(norm->operator()(*tmp) < eps)
						break;
				}

				delete tmp;
			}

		private:
			unsigned int lim;
			double eps;
			INorm<T> *norm;
		};

		template<class T>
		class CG
			:public LEQSolver<T>
		{
		public:
			constexpr CG(unsigned int limit, double eps, INorm<T> &norm):lim(limit), eps(eps), norm(norm.Clone()){}
			~CG(){delete norm;}
			void operator()(IMatrix<T> &m, IVector<T> &x, IVector<T> &b)
			{
				IVector<T> *r = x.Clone(), *p = x.Clone(), *tmp = x.Clone();
				T t, t1, t2, alpha, beta;

				for(unsigned int i = 0; i < x.dim(); ++i)
				{
					r->operator[](i) = b[i];
					for(unsigned int j = 0; j < x.dim(); ++j)
						r->operator[](i) -= m(i, j)*x[j];
					p->operator[](i) = r->operator[](i);
				}

				for(unsigned int i = 0; i < lim; ++i)
				{
					t1 = t2 = 0;
					m(*p, *tmp);
					for(unsigned int j = 0; j < x.dim(); ++j)
					{
						t1 += r->operator[](j)*r->operator[](j);
						t2 += p->operator[](j)*tmp->operator[](j);
					}
					alpha = t1/t2;
					for(unsigned int j = 0; j < x.dim(); ++j)
					{
						x[j] += alpha*p->operator[](j);
						r->operator[](j) -= alpha*tmp->operator[](j);
					}

					if(norm->operator()(*tmp) < eps)
						break;

					t2 = 0;
					for(unsigned int j = 0; j < x.dim(); ++j)
						t2 += r->operator[](j)*r->operator[](j);
					beta = t2/t1;

					for(unsigned int j = 0; j < x.dim(); ++j)
						p->operator[](j) = beta*p->operator[](j) + r->operator[](j);
				}

				delete tmp;
			}

		private:
			unsigned int lim;
			double eps;
			INorm<T> *norm;
		};
	}
}

#endif
