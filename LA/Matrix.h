#ifndef ZARATH_ZNAC_LA_MATRIX_H
#define ZARATH_ZNAC_LA_MATRIX_H

#include "Vector.h"
#include "../basic/general.h"

namespace ZNAC
{
	namespace LA
	{
		template<class T>
		class IMatrix
		{
		public:
			virtual ~IMatrix(){}
			virtual void operator()(IVector<T> &dom, IVector<T> &cod) = 0;
			constexpr virtual T &operator()(unsigned int r, unsigned int c) = 0;
		};

		template<unsigned int Dim, class T = double>
		class Matrix
			:public IMatrix<T>
		{
		public:
			constexpr Matrix():buf(new T[Dim*Dim]){}
			~Matrix(){delete buf;}

			void operator()(IVector<T> &dom, IVector<T> &cod)
			{
				for(unsigned int i = 0; i < Dim; ++i)
				{
					cod[i] = 0;
					for(unsigned int j = 0; j < Dim; ++j)
						cod[i] += this->operator()(i, j)*dom[j];
				}
			}
			constexpr T &operator()(unsigned int r, unsigned int c){return buf[r*Dim + c];}
		private:
			T *buf;
		};

		template<unsigned int Dim, unsigned int diag, class T = double>
		class DiagonalMatrix
			:public IMatrix<T>
		{
		public:
			DiagonalMatrix():buf(new T[Dim*(2*diag + 1) - diag*(diag + 1) + 1]), bufp(new T*[2*diag + 1] + diag)
			{
				bufp[-(int)diag] = buf;
				for(int i = 1; i < diag + 1; ++i)
					bufp[i - (int)diag] = bufp[i - (int)diag - 1] + Dim - diag - 1 + i;
				for(int i = 0; i < diag; ++i)
					bufp[i + 1] = bufp[i] + Dim - i;
			}
			~DiagonalMatrix(){delete [] (bufp - diag); delete [] buf;}

			void operator()(IVector<T> &dom, IVector<T> &cod)
			{
				for(unsigned int r = 0; r < Dim; ++r)
				{
					cod[r] = 0;
					for(unsigned int c = (((int)r - (int)diag < 0)?(0):(r - diag)); c < ((r + diag + 1 > Dim)?(Dim):(r + diag + 1)); ++c)
						cod[r] += bufp[(int)r - (int)c][MIN(r, c)]*dom[c];
				}
			}

			constexpr T &operator()(unsigned int r, unsigned int c){return ((ABS((int)r - (int)c) < (diag + 1))?(bufp[(int)r - (int)c][MIN(r, c)]):(buf[Dim*(diag*2 + 1) - diag*(diag + 1)] = 0));}
		private:
			T *buf;
			T **bufp;
		};
	}
}

#endif
