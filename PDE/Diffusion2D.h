#ifndef ZARATH_ZNAC_PDE_DIFFUSION_2D_H
#define ZARATH_ZNAC_PDE_DIFFUSION_2D_H

#include "../ODE/ODE.h"
#include "Boundary2D.h"

namespace ZNAC
{
	namespace PDE
	{
		template<class T, template<class T>class Boundary, unsigned int D>
		class Diffusion2D
			:public ODE::ODE<T>
		{
		public:
			const T dx, dy;
			const unsigned int Nx, Ny, Param;

			Diffusion2D(Field2D<T> &v, const T &xlen, const T &ylen):dx(xlen/v.Nx), dy(ylen/v.Ny), Nx(v.Nx), Ny(v.Ny), Param(v.Param){}
			~Diffusion2D(){}

			void operator()(LA::Vector<T> &u, LA::Vector<T> &du)
			{
				Boundary<T> B(u, Nx, Ny, Param);
				T dx2inv = 1/(dx*dx);
				T dy2inv = 1/(dy*dy);
				for(unsigned int p = 0; p < Param; ++p)
					for(unsigned int i = 0; i < Ny; ++i)
						for(unsigned int j = 0; j < Nx; ++j)
							if(D == 1)
								du[p*B.Nx*B.Ny + i*B.Nx + j] = ((B(p, i + 1, j) + B(p, i - 1, j)) - 2*B(p, i, j))*dy2inv + ((B(p, i, j + 1) + B(p, i, j - 1)) - 2*B(p, i, j))*dx2inv;
							else if(D == 2)
								du[p*B.Nx*B.Ny + i*B.Nx + j] = (-(B(p, i + 2, j) + B(p, i - 2, j)) + 16*(B(p, i + 1, j) + B(p, i - 1, j)) - 30*B(p, i, j))*dy2inv*(1/12.) + (-(B(p, i, j - 2) + B(p, i, j + 2)) + 16*(B(p, i, j -1) + B(p, i, j + 1)) - 30*B(p, i, j))*dx2inv*(1/12.);
			}
		};

		template<class T, template<class T>class Boundary, unsigned int D>
		class FHN
			:public ODE::ODE<T>
		{
		public:
			const T dx, dy, gamma = 1.0, eps = 0.001, a = 0.125, Du = 1.0, Dv = 0.1;

			FHN(Field2D<T> &v, const T &xlen, const T &ylen):d(v, xlen, ylen), dx(xlen/v.Nx), dy(ylen/v.Ny){}
			~FHN(){}

			void operator()(LA::Vector<T> &u, LA::Vector<T> &du)
			{
				Boundary<T> B(u, d.Nx, d.Ny, d.Param);
				d(u, du);
				for(unsigned int r = 0; r < B.Ny; ++r)
					for(unsigned int c = 0; c < B.Nx; ++c)
					{
						T &x = du[r*B.Nx + c];
						T &y = du[B.Nx*B.Ny + r*B.Nx + c];
						x = Du*x + (1/eps)*(B(0, r, c)*(1 - B(0, r, c))*(B(0, r, c) - a)-B(1, r, c));
						y = Dv*y + B(0, r, c) - gamma*B(1, r, c);
					}
			}

		private:
			Diffusion2D<T, Boundary, D> d;
		};
	}
}

#endif
