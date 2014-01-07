#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

#include "EulerMethod.h"
#include "RKMethod.h"
#include "Real.h"
#include "Dahlquist.h"
#include "DiffusionQuad.h"

using namespace ZNAC::ODE;

int main()
{
	unsigned int Nx , Ny;
	Nx = Ny = 50;
	double dt = 0.25/(Nx*Nx), t = 0;
	double minx, maxx, miny, maxy;
	miny = minx = -1;
	maxx = maxy = 1;
	ODE *D = new Diffusion3pt;
	double iparam[] = {1, 0, 0, 1};

	std::cout << "#Nx dt err\n";
	std::cout << "#RK 3pt\n";
	for(Nx = 10; Nx < 201; Nx += 10)
	{
		DiffusionQuad5pt diff(Nx, Nx, minx, maxx, miny, maxy), ans(Nx, Nx, 0, 0, 0, 0), buf(Nx, Nx, 0, 0, 0, 0);
		for(int delta = 1; delta < 6; ++delta)
		{
			diff.Initialize(iparam, 2, 2);
			dt = delta*0.05*diff.dx*diff.dx;
			RKMethod r(diff, *D, dt);
			t = 0;
			double err = 0, err_max = 0;
			while(t < 1)
			{
				t += dt;
				++r;
				r >> buf;
				diff.Exactly(iparam, 2, 2, t, ans);
				err = 0;
				for(unsigned int i = 0; i < buf.Range(); ++i)
					err += fabs(buf[i] - ans[i])*diff.dx*diff.dx;
				std::cerr << "\rt = " << t << ": err = " << err << "                                                              ";
				if(err > err_max)
					err_max = err;
				else
					break;
			}

			std::cout << Nx << " " << dt << " " << err_max << "\n";
		}
	}

	delete D;
	D = new Diffusion5pt;
	
	std::cout << "#RK 5pt\n";
	for(Nx = 10; Nx < 201; Nx += 10)
	{
		DiffusionQuad5pt diff(Nx, Nx, minx, maxx, miny, maxy), ans(Nx, Nx, 0, 0, 0, 0), buf(Nx, Nx, 0, 0, 0, 0);
		for(int delta = 1; delta < 6; ++delta)
		{
			diff.Initialize(iparam, 2, 2);
			dt = delta*0.05*diff.dx*diff.dx;
			RKMethod r(diff, *D, dt);
			t = 0;
			double err = 0, err_max = 0;
			while(t < 1)
			{
				t += dt;
				++r;
				r >> buf;
				diff.Exactly(iparam, 2, 2, t, ans);
				err = 0;
				for(unsigned int i = 0; i < buf.Range(); ++i)
					err += fabs(buf[i] - ans[i])*diff.dx*diff.dx;
				std::cerr << "\rt = " << t << ": err = " << err << "                                                              ";
				if(err > err_max)
					err_max = err;
				else
					break;
			}

			std::cout << Nx << " " << dt << " " << err_max << "\n";
		}
	}

	delete D;
	D = new Diffusion3pt;
	std::cout << "#Euler 3pt\n";
	for(Nx = 10; Nx < 201; Nx += 10)
	{
		DiffusionQuad5pt diff(Nx, Nx, minx, maxx, miny, maxy), ans(Nx, Nx, 0, 0, 0, 0), buf(Nx, Nx, 0, 0, 0, 0);
		for(int delta = 1; delta < 6; ++delta)
		{
			diff.Initialize(iparam, 2, 2);
			dt = delta*0.05*diff.dx*diff.dx;
			EulerMethod r(diff, *D, dt);
			t = 0;
			double err = 0, err_max = 0;
			while(t < 1)
			{
				t += dt;
				++r;
				r >> buf;
				diff.Exactly(iparam, 2, 2, t, ans);
				err = 0;
				for(unsigned int i = 0; i < buf.Range(); ++i)
					err += fabs(buf[i] - ans[i])*diff.dx*diff.dx;
				std::cerr << "\rt = " << t << ": err = " << err << "                                                              ";
				if(err > err_max)
					err_max = err;
				else
					break;
			}

			std::cout << Nx << " " << dt << " " << err_max << "\n";
		}
	}

	delete D;
	D = new Diffusion5pt;
	
	std::cout << "#Euler 5pt\n";
	for(Nx = 10; Nx < 201; Nx += 10)
	{
		DiffusionQuad5pt diff(Nx, Nx, minx, maxx, miny, maxy), ans(Nx, Nx, 0, 0, 0, 0), buf(Nx, Nx, 0, 0, 0, 0);
		for(int delta = 1; delta < 6; ++delta)
		{
			diff.Initialize(iparam, 2, 2);
			dt = delta*0.05*diff.dx*diff.dx;
			EulerMethod r(diff, *D, dt);
			t = 0;
			double err = 0, err_max = 0;
			while(t < 1)
			{
				t += dt;
				++r;
				r >> buf;
				diff.Exactly(iparam, 2, 2, t, ans);
				err = 0;
				for(unsigned int i = 0; i < buf.Range(); ++i)
					err += fabs(buf[i] - ans[i])*diff.dx*diff.dx;
				std::cerr << "\rt = " << t << ": err = " << err << "                                                              ";
				if(err > err_max)
					err_max = err;
				else
					break;
			}

			std::cout << Nx << " " << dt << " " << err_max << "\n";
		}
	}

	delete D;


}
/*
	for(unsigned int y = 0; y < Ny; ++y)
	{
		for(unsigned int x = 0; x < Nx; ++x)
			std::cout << d(x, y) - ans(x, y) << " ";
		std::cout << "\n";
	}
}*/

