#ifndef ZARATH_ZNAC_LA_LEQ_SOLVER_H
#define ZARATH_ZNAC_LA_LEQ_SOLVER_H

#include "Matrix.h"
#include "Norm.h"

namespace ZNAC
{
	namespace LA
	{
		template<class T>
		class LEQSolver
		{
		public:
			virtual void operator()(const IMatrix<T> &m, IVector<T> &x, const IVector<T> &b) = 0;
		};

		template<class T>
		class LUSolver
			:public LEQSolver<T>
		{
		public:
			void operator()(const IMatrix<T> &m, IVector<T> &x, const IVector<T> &b)
			{
				const unsigned int dim = b;
				LUMatrix<double> L(dim);
				Vector<T> V(dim);
				L << m;

				for(unsigned int i = 0; i < dim; ++i)
				{
					V[i] = b[i];
					for(unsigned int j = 0; j < i; ++j)
						V[i] -= L(i, j)*V[j];
				}

				for(unsigned int i = dim - 1; i != -1; --i)
				{
					x[i] = V[i]/L(i, i);
					for(unsigned int j = i + 1; j < dim; ++j)
						x[i] -= L(i, j)*x[j];
				}
			}
		};

		template<class T>
		class Gauss
			:public LEQSolver<T>
		{
		public:
			void operator()(const IMatrix<T> &m, IVector<T> &x, const IVector<T> &b)
			{
				GaussMatrix<T> G(b);
				Vector<T> V(b);
				G = m;
				V = b;

				for(unsigned int r = 0; r < b; ++r)
				{
					//normalize
					for(unsigned int i = r; i < b; ++i)
					{
						T max = 0;
						for(unsigned int j = i; j < b; ++j)
							max = max < ABS(G(i, j)) ? ABS(G(i, j)) : max;
						max = 1/max;
						for(unsigned int j = 0; j < b; ++j)
							G(i, j) *= max;
						V[i] *= max;
					}


					//pivot select
					T max = 0;
					unsigned int maxi = 0;
					for(unsigned int i = r; i < b; ++i)
						if(max < ABS(G(i, r)))
							max = ABS(G(i, r)), maxi = i;

					if(max == 0)
						return;
					G.Swap(maxi, r);
					max = V[maxi];
					V[maxi] = V[r];
					V[r] = max;

					//erase
					for(unsigned int i = r + 1; i < b; ++i)
					{
						max = G(i, r)/G(r, r);
						for(unsigned int c = r; c < b; ++c)
							G(i, c) -= G(r, c)*max;
						V[i] -= V[r]*max;
					}
				}

				for(unsigned int r = b - 1; r != -1; --r)
				{
					x[r] = V[r];
					for(unsigned int i = r + 1; i < b; ++i)
						x[r] -= x[i]*G(r, i);
					x[r] /= G(r, r);
				}
			}
		};

		template<class T>
		class Jacobi
			:public LEQSolver<T>
		{
		public:
			constexpr Jacobi(unsigned int limit, double eps, INorm<T> &norm):lim(limit), eps(eps), norm(norm.Clone()){}
			~Jacobi(){delete norm;}
			void operator()(const IMatrix<T> &m, IVector<T> &x, const IVector<T> &b)
			{
				Vector<T> *tmp = b.Clone();
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
			void operator()(const IMatrix<T> &m, IVector<T> &x, const IVector<T> &b)
			{
				Vector<T> *tmp = b.Clone();
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
			void operator()(const IMatrix<T> &m, IVector<T> &x, const IVector<T> &b)
			{
				Vector<T> *r = x.Clone(), *p = x.Clone(), *tmp = x.Clone();
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
