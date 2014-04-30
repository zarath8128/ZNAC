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
			virtual unsigned int N() const = 0;
		};


		template<class T = double>
		class Vector
			:public IVector<T>
		{
		public:
			Vector(unsigned int Dim):buf(new T[Dim]), Dim(Dim){}
			Vector(const IVector<T> &v):buf(new T[v]), Dim(v){for(unsigned int i = 0; i < Dim; ++i)buf[i] = v[i];}
			template<class... TT>
			Vector(const T &v, const TT&... arg){Initialize(0u, v, arg...);}
			virtual ~Vector(){delete [] buf;}

			Vector &operator=(const IVector<T> &v){for(unsigned int i = 0; i < *this; ++i)buf[i] = v[i];return *this;}
			Vector &operator=(Vector<T> &&v){buf = v.buf; v.buf = nullptr; return *this;}
			virtual const T& operator[](unsigned int i) const{return buf[i];}
			virtual T& operator[](unsigned int i){return buf[i];}
			constexpr unsigned int N() const {return Dim;}
			constexpr operator T*() const {return buf;}
		protected:
			T *buf;
			unsigned int Dim;

		private:
			template<class... TT>
			void Initialize(unsigned int Dim, const T& u, const TT&... arg){Initialize(Dim + 1, arg...);buf[Dim] = u;};
			void Initialize(unsigned int Dim, const T& u){buf = new T[Dim + 1];this->Dim = Dim + 1;buf[Dim] = u;}
		};

		template<unsigned int Dim, class T = double>
		class StackVector
			:public IVector<T>
		{
		public:
			virtual const T& operator[](unsigned int i) const{return buf[i];}
			virtual T& operator[](unsigned int i){return buf[i];}
			constexpr unsigned int N() const {return Dim;}
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
			constexpr unsigned int N() const {return Dim;}
		private:
			T * const buf;
			const unsigned int Dim;
		};

		template<unsigned int dim, class T = double>
		class StaticVector
			:public IVector<T>
		{
		public:
			template<class... Args>
			StaticVector(const Args&... args):StaticVector(0u, args...){}
			const T& operator[](unsigned int i) const{return buf[i];}
			T& operator[](unsigned int i){return buf[i];}
			constexpr unsigned int N() const{return dim;}
		private:
			T buf[dim];

			template<class... Args>
			StaticVector(unsigned int i, const T &val, const Args&... args):StaticVector(i + 1, args...){buf[i] = val;}
			StaticVector(unsigned int i, const T &val){buf[i] = val;}
		};
	}
}

#endif
