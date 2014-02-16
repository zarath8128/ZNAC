#ifndef ZARATH_ZNAC_LA_VECTOR_H
#define ZARATH_ZNAC_LA_VECTOR_H

#include "../basic/general.h"

namespace ZNAC
{
	namespace LA
	{
		template<class T>
		class IVector
			:public IClonable<IVector<T> >
		{
		public:
			virtual ~IVector(){}
			constexpr virtual T& operator[](unsigned int i) = 0;
			constexpr virtual unsigned int dim() = 0;
			constexpr virtual IVector<T> *Clone() = 0;
		};

		template<unsigned int Dim, class T = double>
		class Vector
			:public IVector<T>
		{
		public:
			Vector():buf(new T[Dim]){}
			~Vector(){delete [] buf;}

			constexpr T& operator[](unsigned int i){return buf[i];}
			constexpr unsigned int dim(){return Dim;}
			constexpr IVector<T> *Clone(){return new Vector<Dim, T>;}
		private:
			T *buf;
		};
	}
}

#endif
