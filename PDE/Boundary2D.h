#ifndef ZARATH_ZNAC_PDE_BOUNDARY_2D_H
#define ZARATH_ZNAC_PDE_BOUNDARY_2D_H

#include "../LA/Vector.h"

namespace ZNAC
{
	namespace PDE
	{
		template<class T = double>
		class Field2D
			:public LA::Vector<T>
		{
		public:
			const unsigned int Nx, Ny, Param;

			Field2D(unsigned int param, unsigned int xdim, unsigned int ydim):Nx(xdim), Ny(ydim), Param(param), LA::Vector<T>(xdim*ydim*param){}

			T &operator()(unsigned int p, unsigned int r, unsigned int c){return LA::Vector<T>::buf[p*Nx*Ny + r*Nx + c];}
		};


		template<class T = double>
		class Vector2D
			:public LA::Vector<T>
		{
		public:
			const unsigned int Nx, Ny;

			Vector2D():Vector2D(0, 0){}
			Vector2D(unsigned int xdim, unsigned int ydim):LA::Vector<T>(xdim*ydim), Nx(xdim), Ny(ydim){}

			T &operator()(unsigned int r, unsigned int c){return this->operator[](r*Nx + c);}

		};

		template<class T>
		class Boundary2D
		{
		public:
			const unsigned int Nx, Ny, Param;

			Boundary2D(LA::Vector<T> &v, unsigned int Nx, unsigned int Ny, unsigned int Params):v(v), Nx(Nx), Ny(Ny), Param(Param){}
			virtual ~Boundary2D(){}
			constexpr virtual const T &operator()(unsigned int p, int r, int c) = 0;
		protected:
			LA::Vector<T> &v;
		};

		template<class T>
		class Neumann2D
			:public Boundary2D<T>
		{
		public:
			Neumann2D(LA::Vector<T> &v, unsigned int Nx,unsigned int Ny, unsigned int Params):Boundary2D<T>(v, Nx, Ny, Params){}
			constexpr const T &operator()(unsigned int p, int r, int c)override{return Boundary2D<T>::v[p*Boundary2D<T>::Nx*Boundary2D<T>::Ny + y(r)*Boundary2D<T>::Nx + x(c)];}

			constexpr unsigned int x(int i){return ((i < 0)?(-i - 1):((i > Boundary2D<T>::Nx - 1)?(Boundary2D<T>::Nx - (i - Boundary2D<T>::Nx + 1)):(i)));}
			constexpr unsigned int y(int i){return ((i < 0)?(-i - 1):((i > Boundary2D<T>::Ny - 1)?(Boundary2D<T>::Ny - (i - Boundary2D<T>::Ny + 1)):(i)));}
		};
	}
}

#endif
