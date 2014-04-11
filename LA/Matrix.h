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
			virtual void operator()(const IVector<T> &dom, IVector<T> &cod) = 0;
			virtual T &operator()(unsigned int r, unsigned int c) = 0;
			virtual const T &operator()(unsigned int r, unsigned int c) const = 0;
		};

		template<class T = double>
		class Matrix
			:public IMatrix<T>
		{
		public:
			constexpr Matrix(unsigned int Dim):buf(new T[Dim*Dim]), Dim(Dim){}
			~Matrix(){delete [] buf;}

			virtual void operator()(const IVector<T> &dom, IVector<T> &cod)
			{
				for(unsigned int i = 0; i < Dim; ++i)
				{
					cod[i] = 0;
					for(unsigned int j = 0; j < Dim; ++j)
						cod[i] += this->operator()(i, j)*dom[j];
				}
			}
			virtual T &operator()(unsigned int r, unsigned int c){return buf[r*Dim + c];}
			virtual const T &operator()(unsigned int r, unsigned int c) const {return buf[r*Dim + c];}
		protected:
			T *buf;
			const unsigned int Dim;
		};

		template<class T = double>
		class LUMatrix
			:public Matrix<T>
		{
		public:
			LUMatrix(unsigned int Dim):Matrix<T>(Dim), pbuf(new T*[2*Dim - 2]), rbuf(pbuf - 1), cbuf(pbuf + Dim - 1), dbuf(nullptr), IsEnable(false)
			{
				for(unsigned int i = 1; i < Dim; ++i)
					rbuf[i] = Matrix<T>::buf + i*(i - 1)/2;
				for(unsigned int i = 1; i < Dim; ++i)
					cbuf[i] = Matrix<T>::buf + Dim*(Dim - 1)/2 + i*(i - 1)/2;
				dbuf = Matrix<T>::buf + Dim*(Dim - 1);
			}

			void operator<<(const IMatrix<T> &m)
			{
				dbuf[0] = m(0, 0);
				for(unsigned int i = 1; i < Matrix<T>::Dim; ++i)
				{
					for(unsigned int j = 0; j < i; ++j)
					{
						cbuf[i][j] = m(j, i);
						rbuf[i][j] = m(i, j);
						for(unsigned int k = 0; k < j; ++k)
						{
							cbuf[i][j] -= cbuf[i][k]*rbuf[j][k]*dbuf[k];
							rbuf[i][j] -= cbuf[j][k]*rbuf[i][k]*dbuf[k];
						}
						cbuf[i][j] /= dbuf[j];
						rbuf[i][j] /= dbuf[j];
					}

					dbuf[i] = m(i, i);
					for(unsigned int j = 0; j < i; ++j)
						dbuf[i] -= cbuf[i][j]*rbuf[i][j]*dbuf[j];
					if(ABS(dbuf[i]) == 0)
					{
						IsEnable = false;
						return;
					}

				}
				IsEnable = true;
			}

			void operator>>(IMatrix<T> &m)
			{
				m(0, 0) = dbuf[0];
				for(unsigned int i = 1; i < Matrix<T>::Dim; ++i)
				{
					m(i, i) = dbuf[i];
					for(unsigned int j = 0; j < i; ++j)
						m(i, i) += rbuf[i][j]*cbuf[i][j]*dbuf[j];

					for(unsigned int j = 0; j < i; ++j)
					{
						m(i, j) = rbuf[i][j]*dbuf[j];
						m(j, i) = cbuf[i][j]*dbuf[j];
						for(unsigned int k = 0; k < j; ++k)
						{
							m(i, j) += rbuf[j][k]*cbuf[i][k]*dbuf[k];
							m(j, i) += rbuf[i][k]*cbuf[j][k]*dbuf[k];
						}
					}
				}
			}

			void operator()(const IVector<T> &dom, IVector<T> &cod){Matrix<T>::operator()(dom, cod);}
			T &operator()(unsigned int r, unsigned int c){return (r == c ? dbuf[r] : (r > c ? rbuf[r][c]: cbuf[c][r]));}
			virtual const T &operator()(unsigned int r, unsigned int c) const{return (r == c ? dbuf[r] : (r > c ? rbuf[r][c]: cbuf[c][r]));}
			operator bool() const{return IsEnable;}

		protected:
			T **pbuf, **rbuf, **cbuf, *dbuf;
			bool IsEnable;
		};

		template<class T = double>
		class GaussMatrix
			:public Matrix<T>
		{
		public:
			GaussMatrix(unsigned int Dim):Matrix<T>(Dim), rbuf(new T*[Dim])
			{
				rbuf[0] = Matrix<T>::buf;
				for(unsigned int i = 1; i < Dim; ++i)
					rbuf[i] = rbuf[i - 1] + Dim;
			}

			~GaussMatrix(){delete [] rbuf;}

			virtual void operator()(const IVector<T> &dom, IVector<T> &cod){Matrix<T>::operator()(dom, cod);}

			void Swap(unsigned int i, unsigned int j){T *b = rbuf[i]; rbuf[i] = rbuf[j]; rbuf[j] = b;}

			void operator=(const IMatrix<T> &m)
			{
				for(unsigned int i = 0; i < Matrix<T>::Dim; ++i)
					for(unsigned int j = 0; j < Matrix<T>::Dim; ++j)
						(*this)(i, j) = m(i, j);
			}
			virtual T &operator()(unsigned int r, unsigned int c){return rbuf[r][c];}
			virtual const T &operator()(unsigned int r, unsigned int c) const{return rbuf[r][c];}
		protected:
			T **rbuf;
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

			T &operator()(unsigned int r, unsigned int c){return ((ABS((int)r - (int)c) < (diag + 1))?(bufp[(int)r - (int)c][MIN(r, c)]):(buf[Dim*(diag*2 + 1) - diag*(diag + 1)] = 0));}
		private:
			T *buf;
			T **bufp;
		};
	}
}

#endif
