#ifndef ZARATH_ZNAC_ETC_DELAUNAY_TRIANGULATION_H
#define ZARATH_ZNAC_ETC_DELAUNAY_TRIANGULATION_H

#include "basic/buffer.h"

namespace ZNAC
{
	namespace etc
	{
		template<unsigned int dim>
		class Point
		{
		public:
			double &operator[](unsigned int i){return x[i];}
		protected:
			double x[dim];
		};

		double Norm(const Point<dim>& a, const Point<dim>& b)
		{
			double tmp = 0;
			for(unsigned int i = 0; i < dim; ++i)
				tmp = a[i]*a[i] + b[i]*b[i];
			return tmp;
		}

		template<unsigned int dim>
		class Simplex
		{
		public:
			unsigned int operator[](unsigned int i){return p[i];}
		protectd:
			unsigned int p[dim + 1];
		};

		template<unsigned int dim>
		void DelaunayTriangulation(double *points, unsigned int point_num, double **topology, unsigned int *topology_nums, void *&buffer)
		{
			Array<Point<dim>> P;
			Array<Simplex<dim>> S;
			Array<unsigned int> Done;
			Point<dim> ptmp;
			Simplex<dim> stmp;

			for(unsigned i = 0; i < dim + 1; ++i)
			{
				for(unsigned j = 0; j < dim; ++j)
					ptmp[j] = (i == j ? -1 : 1 )*1e6;
				P << ptmp;
				stmp[i] = i;
			}

			for(unsigned int i = 0; i < point_num; ++i)
			{
				for(unsigned int j = 0; j < dim; ++j)
					ptmp[j] = points[i*dim + j];
				P << std::move(ptmp);
			}

		}
	}
}

#endif
