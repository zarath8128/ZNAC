#ifndef ZARATH_ZNAC_LA_VECTOR_H
#define ZARATH_ZNAC_LA_VECTOR_H

#include "../basic/general.h"

namespace ZNAC
{
	namespace LA
	{
		template<class T>
		class IVector
		{
		public:
			virtual ~IVector(){}
			virtual const T &operator[](unsigned int i) const = 0;
			virtual T &operator[](unsigned int i) = 0;
			virtual operator unsigned int() const = 0;
		};


		template<class T = double>
		class Vector
			:public IVector<T>
		{
		public:
			Vector(unsigned int Dim):buf(new T[Dim]), Dim(Dim){}
			virtual ~Vector(){delete [] buf;}

			Vector &operator=(const IVector<T> &v){for(unsigned int i = 0; i < *this; ++i)buf[i] = v[i];return *this;}
			Vector &operator=(Vector<T> &&v){buf = v.buf; v.buf = nullptr; return *this;}
			virtual const T& operator[](unsigned int i) const{return buf[i];}
			virtual T& operator[](unsigned int i){return buf[i];}
			constexpr operator unsigned int() const {return Dim;}
		protected:
			T *buf;
			const unsigned int Dim;
		};

		template<unsigned int Dim, class T = double>
		class StackVector
			:public IVector<T>
		{
		public:
			virtual const T& operator[](unsigned int i) const{return buf[i];}
			virtual T& operator[](unsigned int i){return buf[i];}
			virtual operator unsigned int() const {return Dim;}
		protected:
			T buf[Dim];
		};

		template<class T = double>
		class WrapVector
			:public IVector<T>
		{
		public:
			WrapVector(unsigned int Dim, T *buf):buf(buf), Dim(Dim){}
			const T& operator[](unsigned int i) const{return buf[i];}
			T& operator[](unsigned int i){return buf[i];}
			operator unsigned int() const {return Dim;}
		private:
			T const *buf;
			const unsigned int Dim;
		};
	}
}

#endif
