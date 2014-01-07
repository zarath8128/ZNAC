#ifndef ZARATH_ZNAC_ODE_DIFFUSION_H
#define ZARATH_ZNAC_ODE_DIFFUSION_H

#define _USE_MATH_DEFINES
#include <cmath>
#include "ODE.h"
#include <iostream>

namespace ZNAC
{
	namespace ODE
	{
		class Boundary;
		class DiffusionQuad;

		class Boundary
		{
		public:
			void buffer(double *&buf, double **&u, double **&ubuf);
		};

		class DiffusionQuad5pt
			:public Domain
		{
		public:
			DiffusionQuad5pt(unsigned int Nx, unsigned int Ny, double minx, double maxx, double miny, double maxy)
				:Nx(Nx), Ny(Ny), minx(minx), maxx(maxx), miny(miny), maxy(maxy), dx((maxx - minx)/Nx), dy((maxy - miny)/Ny)
			{
				buf = new double[(Nx + 4)*(Ny + 4) - 12];
				ubuf = new double*[Ny + 4];
				u = ubuf + 2;
				u[-2] = buf;
				u[-1] = u[-2] + Nx + 1;
				u[0] = u[-1] + Nx + 3;
				for(unsigned int i = 1; i < Ny; ++i)
					u[i] = u[i - 1] + Nx + 4;
				u[Ny] = u[Ny - 1] + Nx + 3;
				u[Ny + 1] = u[Ny] + Nx + 1;
			}
			~DiffusionQuad5pt()
			{
				delete [] buf;
				delete [] ubuf;
			}

			void Initialize(double *param, unsigned int Px, unsigned int Py)
			{
				for(unsigned int y = 0; y < Ny; ++y)
				for(unsigned int x = 0; x < Nx; ++x)
				{
					u[y][x] = 0;
					for(int py = 0; py < Py; ++py)
					for(int px = 0; px < Px; ++px)
						u[y][x] += param[py*Px + px]*cos(px*M_PI*(x + 0.5)/Nx)*cos(py*M_PI*(y + 0.5)/Ny);
				}
			}

			void Exactly(double *param, unsigned int Px, unsigned int Py, double t, DiffusionQuad5pt &ans)
			{
				for(unsigned int y = 0; y < Ny; ++y)
				for(unsigned int x = 0; x < Nx; ++x)
				{
					ans(x, y) = 0;
					for(int py = 0; py < Py; ++py)
					for(int px = 0; px < Px; ++px)
					{
						ans(x, y) += exp(-(px*px*M_PI*M_PI/((maxx - minx)*(maxx - minx)) + py*py*M_PI*M_PI/((maxy - miny)*(maxy - miny)))*t)*param[py*Px + px]*cos(px*M_PI*(x + 0.5)/Nx)*cos(py*M_PI*(y + 0.5)/Ny);
						//std::cout << "(" << x << ", " << y << ") " << ans(x, y) << std::endl;
					}
				}
			}

			void update()
			{
				u[-1][-1] = u[0][0];
				u[-1][Nx] = u[0][Nx - 1];
				u[Ny][-1] = u[Ny - 1][0];
				u[Ny][Nx] = u[Ny - 1][Nx - 1];

				for(unsigned int x = 0; x < Nx; ++x)
				{
					u[-1][x] = u[0][x];
					u[-2][x] = u[1][x];
					u[Ny][x] = u[Ny - 1][x];
					u[Ny + 1][x] = u[Ny - 2][x];
				}

				for(unsigned int y = 0; y < Ny; ++y)
				{
					u[y][-1] = u[y][0];
					u[y][-2] = u[y][1];
					u[y][Nx] = u[y][Nx - 1];
					u[y][Nx + 1] = u[y][Nx - 2];
				}
			}

			unsigned int Range(){return Nx*Ny;}

			Domain *Clone(){return new DiffusionQuad5pt(Nx, Ny, minx, maxx, miny, maxy);}

			double &operator()(int x, int y){return u[y][x];}
			double &operator[](unsigned int i){return u[i / Nx][i % Nx];}

			const unsigned int Nx, Ny;
			const double dx, dy;
		protected:
			double minx, maxx, miny, maxy;
			double *buf;
			double **u, **ubuf;
		};

		class Diffusion5pt
			:public ODE
		{
		public:
			void operator()(Domain &u, Domain &du)
			{
				DiffusionQuad5pt &a = (DiffusionQuad5pt&)u, &b = (DiffusionQuad5pt&)du;
				a.update();
				for(int y = 0; y < a.Ny; ++y)
				for(int x = 0; x < a.Nx; ++x)
				{	//dx == dy
					b(x, y) = (1./12)*(-((a(x - 2, y) + a(x + 2, y)) + (a(x, y - 2) + a(x, y + 2))) + 16*((a(x - 1, y) + a(x + 1, y)) + (a(x, y - 1) + a(x, y + 1))) - 60*a(x, y))/(a.dx*a.dy);
				}
			}
		};

		class Diffusion3pt
			:public ODE
		{
		public:
			void operator()(Domain &u, Domain &du)
			{
				DiffusionQuad5pt &a = (DiffusionQuad5pt&)u, &b = (DiffusionQuad5pt&)du;
				a.update();
				for(int y = 0; y < a.Ny; ++y)
				for(int x = 0; x < a.Nx; ++x)
				{	//dx == dy
					b(x, y) = (((a(x - 1, y) + a(x + 1, y)) + (a(x, y - 1) + a(x, y + 1))) - 4*a(x, y))/(a.dx*a.dy);
				}
			}
		};
	
	}
}

#endif
