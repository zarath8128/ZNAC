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
	}
}

#endif
