//This header is implimentation of high-dimension Dlaunay Triangulation.
//but, this source requires less than or equal 3 dimension.
//						written by Mamoru OKAMOTO
#ifndef ZARATH_ZNAC_ETC_DELAUNAY_TRIANGULATION_H
#define ZARATH_ZNAC_ETC_DELAUNAY_TRIANGULATION_H

#include "basic/buffer.h"
#include "LA/LEQSolver.h"

namespace ZNAC
{
	namespace etc
	{
		template<unsigned int dim>
		class Point
		{
		public:
			Point(){}

			template<class... Params>
			Point(Params... param)
			{
				Set(0, param...);
			}

			double &operator[](unsigned int i){return x[i];}
			const double &operator[](unsigned int i) const {return x[i];}
		protected:
			double x[dim];

		private:

			template<class T, class... Params>
			void Set(unsigned int index, T x0, Params... param)
			{
				x[index] = x0;
				Set(++index, param...);
			}
			void Set(unsigned int index){}
		};

		template<unsigned int dim>
		double Norm(const Point<dim>& a, const Point<dim>& b)
		{
			double tmp = 0;
			for(unsigned int i = 0; i < dim; ++i)
				tmp = (a[i] - b[i])*(a[i] - b[i]);
			return tmp;
		}

		template<unsigned int dim>
		class SuperPlane
		{
		public:
			SuperPlane(Point<dim> *points)
			{
				LA::Matrix<double> m(dim);
				LA::StackVector<dim, double> v, x;
				for(unsigned int r = 0; r < dim; ++r)
				{
					v[r] = 1;
					for(unsigned int c = 0; c < dim; ++c)
						m(r, c) = points[c][r];
				}

				LA::LUSolver<double>()(m, x, v);

				for(unsigned int i = 0; i < dim; ++i)
					a[i] = x[i];

				for(unsigned int i = 0; i < dim; ++i)
					std::cout << "a[" << i << "] = " << a[i] << std::endl;
			}

			int operator()(Point<dim> &p)
			{
				double tmp = 0;
				for(unsigned int i = 0; i < dim; ++i)
					tmp += a[i]*p[i];
				return tmp == 1 ? 0 : (tmp > 1 ? 1 : -1);
			}

		protected:
			double a[dim];
		};

		template<unsigned int dim>
		class Simplex
		{
		public:
			unsigned int &operator[](unsigned int i){return p[i];}
			const unsigned int &operator[](unsigned int i) const{return p[i];}
		protected:
			unsigned int p[dim + 1];
		};

		//Circumscribed Sphere's center and radius^2
		template<unsigned int dim>
		void CS(const Array<Point<dim>> &P, const Simplex<dim> &s, double &r2, Point<dim> &c)
		{
			LA::Matrix<double> m(dim);
			for(unsigned int r = 0; r < dim; ++r)
				for(unsigned int c = 0; c < dim; ++c)
					m(r, c) = 2*(P[s.p[r + 1]][c] - P[s.p[r]][c]);
			LA::StackVector<dim, double> v, x;
			for(unsigned int i = 0; i < dim; ++i)
			{
				v[i] = 0;
				for(unsigned int j = 0; j < dim; ++j)
					v[i] += P[s.p[i + 1]][j]*P[s.p[i + 1]][j] - P[s.p[i]][j]*P[s.p[i]][j];
			}

			LA::LUSolver<double>()(m, x, v);

			r2 = 0;
			for(unsigned int i = 0; i < dim; ++i)
				c[i] = x[i], r2 += (c[i] - P[s.p[0]][i])*(c[i] - P[s.p[0]][i]);
		}

		template<unsigned int dim>
		bool IsProper(const Array<Point<dim>> &P, const Simplex<dim> &s, unsigned int p)
		{
			double r2;
			Point<dim> c;
			CS(P, s, r2, c);
			return Norm(c, P[p]) > r2;
		}



		template<unsigned int dim>
		int Divide(Array<Point<dim>> &P, Array<Simplex<dim>> &S, Array<Simplex<dim>> &Add, unsigned int s, unsigned int p)
		{
			Point<dim> points[dim];
			unsigned int antipodes = -1;
			
			for(unsigned int i = 0; i < dim + 1; ++i)
			{
				for(unsigned int t = 0, j = 0; j < dim + 1; ++j)
					if(j != i)
						points[t++] = P[S[s][j]];
				SuperPlane<dim> SP(points);

				if(SP(P[i])*SP(P[p]) < -1)
				{
					antipodes = i;
					break;
				}
			}

			if(antipodes == -1)
			{
				std::cerr << "error ocurred:\n\tcouldn't detect antipodes\n";
				return -1;
			}

			Simplex<dim> sim, tmp;

			sim = S[s];
			S.Remove(s);

			for(unsigned int i = 0; i < dim + 1; ++i)
			{
				tmp[0] = p;
				tmp[1] = antipodes;
				for(unsigned int t = 2, j = 0; j < dim + 1 && t < dim + 1; ++j)
					if(sim[j] != antipodes && i != j)
						tmp[t++] = sim[j];
				Add << std::move(tmp);
			}
		}

		template<unsigned int dim>
		void AddPoint(Array<Point<dim>> &P, Array<Simplex<dim>> &S, unsigned int p)
		{
			for(unsigned int i = 0; i < S.Used; ++i)
				if(!IsProper(P, S[i], p))
				{
					Array<Simplex<dim>> add;
					Divide(P, S, add, i, p);
					for(unsigned int j = 0; j < add.Used; ++j)
						AddSimplex(P, S, add[j]);
				}
		}

		template<unsigned int dim>
		void AddSimplex(Array<Point<dim>> &P, Array<Simplex<dim>> &S, unsigned int s)
		{
			for(unsigned int i = 0; i < P.Used; ++i)
				if(!IsProper(P, S[s], i))
				{
					Array<Simplex<dim>> add;
					Divide(P, S, add, s, i);
					for(unsigned int j = 0; j < add.Used; ++j)
						AddSimplex(P, S, add[j]);
				}
		}

		template<unsigned int dim>
		//void DelaunaySimplexion(double *points, unsigned int point_num, double **topology, unsigned int *topology_nums, void *&buffer)
		void DelaunaySimplexion(Array<Point<dim>> &P, Array<Simplex<dim>> &S)
		{
			//Array<Point<dim>> P;
			//Array<Simplex<dim>> S;
			Array<unsigned int> Done;
			Point<dim> ptmp;
			Simplex<dim> stmp;

			//configuration of outer simplex;
			for(unsigned i = 0; i < dim + 1; ++i)
			{
				for(unsigned j = 0; j < dim; ++j)
					ptmp[j] = (i == j ? -1 : 1 )*1e6;
				P.Add(i, std::move(ptmp));
				stmp[i] = i;
			}

			S << std::move(stmp);

			//for all points
			//for(unsigned int i = 0; i < point_num; ++i)
			for(unsigned int i = dim; i < P.Used; ++i)
			{
				//reading from points into ptmp;
				//for(unsigned int j = 0; j < dim; ++j)
					//ptmp[j] = points[i*dim + j];

				//P << ptmp;

				AddPoint(P, S, i);
			}
		}
	}
}

#endif
