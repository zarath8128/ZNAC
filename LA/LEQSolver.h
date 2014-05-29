#ifndef ZARATH_ZNAC_LA_LEQ_SOLVER_H
#define ZARATH_ZNAC_LA_LEQ_SOLVER_H

#include "Matrix.h"
#include "Norm.h"
#include <iostream>
#include <cstdint>
#include <cassert>

namespace ZNAC
{
	namespace LA
	{
/*		template<class T>
		class LUSolver
		{
		public:
			template<class MATRIX, class U>
			void operator()(const MATRIX &m, IVector<T> &x, const IVector<T> &b, const U &u)
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
*/
/*		template<class T>
		class Gauss
		{
		public:
			template<class MATRIX, class U>
			void operator()(const MATRIX &m, IVector<T> &x, const IVector<T> &b, const U &u)
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
*/
/*		template<class T>
		class Jacobi
		{
		public:
			constexpr Jacobi(unsigned int limit, double eps, INorm<T> &norm):lim(limit), eps(eps), norm(norm.Clone()){}
			~Jacobi(){delete norm;}
			template<class MATRIX, class U>
			void operator()(const MATRIX &m, IVector<T> &x, const IVector<T> &b, const U& u)
			{
				Vector<T> *tmp = b.Clone();
				T t;
				for(unsigned int i = 0; i < lim; ++i)
				{
					for(unsigned int r = 0; r < b.N(); ++r)
					{
						tmp->operator[](r) = b[r];
						for(unsigned int c = 0; c < b.N(); ++c)
							tmp->operator[](r) -= m(r, c)*x[c];
						tmp->operator[](r) /= m(r, r);
						tmp->operator[](r) += x[r];
					}

					for(unsigned int r = 0; r < b.N(); ++r)
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
*/
/*		template<class T>
		class GaussSeidel
		{
		public:
			constexpr GaussSeidel(unsigned int limit, double eps, INorm<T> &norm):lim(limit), eps(eps), norm(norm.Clone()){}
			~GaussSeidel(){delete norm;}

			template<class MATRIX, class U>
			void operator()(const MATRIX &m, IVector<T> &x, const IVector<T> &b, const U& u)
			{
				Vector<T> *tmp = b.Clone();
				T t;
				for(unsigned int i = 0; i < lim; ++i)
				{
					for(unsigned int r = 0; r < b.N(); ++r)
					{
						tmp->operator[](r) = x[r];
						x[r] = b[r];
						for(unsigned int c = 0; c < r; ++c)
							x[r] -= m(r, c)*x[c];
						x[r] /= m(r, r);
						x[r] += tmp->operator[](r);
					}

					for(unsigned int r = 0; r < b.N(); ++r)
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
*/
		template<class T>
		class CG
		{
		public:
			unsigned int n = 0;
			unsigned int rep = 0;
			double err = 0;

			constexpr CG(unsigned int limit, unsigned int restart, double eps)
				:lim(limit), restart(restart), eps(eps), IsComplete(false){}
			~CG(){}

			template<class MATRIX, class VALID_INDEX>
			void operator()(const MATRIX &m, IVector<T> &x, const IVector<T> &b, const VALID_INDEX &valid)
			{
				assert(x.N() == b.N());
				Vector<T> r(x.N()), p(x.N()), tmp(x.N()), b_local(x.N());
				for(unsigned int i = 0; i < x.N(); ++i)
					r[i] = p[i] = tmp[i] = b_local[i] = 0;
				T t1, t2, alpha, beta = 0, b_euclid = 0;
				rep = 0;
				n = 0;

				for(auto &i : valid)
					b_euclid += b[i]*b[i], b_local[i] = b[i];

				for(unsigned int k = 0; k < lim; ++k)
				{
					m(x, r);

					t1 = t2 = 0;
					for(auto &i : valid)
						r[i] = b_local[i] - r[i], t2 += r[i]*r[i];

					for(unsigned int i = 0; i < restart; ++i)
					{
						if(t2 < eps*b_euclid || (t2 < eps && b_euclid < eps))
							goto CG_SUCCESS;

						for(auto &j : valid)
							p[j] = beta*p[j] + r[j];

						m(p, tmp);

						t1 = 0;
						for(auto &j : valid)
							t1 += p[j]*tmp[j];

						if(t1 == 0 && t2 == 0)
							goto CG_SUCCESS;

						if(t1 == 0)
							goto CG_FAILED;

						alpha = t2/t1;

						if(IsNaN(alpha))
							goto CG_FAILED;

						t2 = 0;

						for(auto &j : valid)
						{
							x[j] += alpha*p[j];
							r[j] -= alpha*tmp[j];
							t2 += r[j]*r[j];
						}

						++n;
						beta = (t1 == 0 ? 1 : t2/(alpha*t1));

#ifdef CG_VERBOSE
						std::cerr << "error = " << (b_euclid ? t2/b_euclid : t2) << std::endl;
	 					std::cerr << "alpha   = " << alpha <<  std::endl;
	 					std::cerr << "beta    = " << beta <<  std::endl;
	 					std::cerr << "t1      = " << t1 <<  std::endl;
	 					std::cerr << "t2      = " << t2 <<  std::endl;
	 					std::cerr << "b_euclid= " << b_euclid <<  std::endl;
#endif
					}
					rep++;
#ifdef CG_VERBOSE
	 				std::cerr << "restarted:" << k + 1 << std::endl;
#endif
				}
CG_FAILED:
				IsComplete = false;
#ifdef CG_VERBOSE
 				std::cerr << "CG Method failed" <<  std::endl;
				std::cerr << "alpha = " << alpha <<  std::endl;
	 			std::cerr << "beta  = " << beta <<  std::endl;
	 			std::cerr << "t1    = " << t1 <<  std::endl;
	 			std::cerr << "t2    = " << t2 <<  std::endl;
	 			std::cerr << "b_euclid= " << b_euclid <<  std::endl;
#endif
				return;

CG_SUCCESS:
				IsComplete = true;
#ifdef CG_VERBOSE
	 			std::cerr << "CG Method Completed!" << std::endl;
#endif
				return;
			}

			operator bool() const {return IsComplete;}

			const unsigned int lim, restart;
			const double eps;

		private:
			bool IsComplete;
		};
	}
}

#endif
