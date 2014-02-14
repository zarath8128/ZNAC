#ifndef ZARATH_ZNAC_LA_NORM_H
#define ZARATH_ZNAC_LA_NORM_H

#include "Vector.h"
#include <cmath>

namespace ZNAC
{
	namespace LA
	{
		template<class T>
		class absNorm
		{
		public:
			virtual ~absNorm(){}
			constexpr virtual T operator()(absVector<T> &v) = 0;
			virtual absNorm *Clone() = 0;
		};

		template<class T>
		class lNorm
		:public absNorm<T>
		{
		public:
			lNorm(double p):p(p){}

			absNorm<T> *Clone(){return new lNorm(p);}

			constexpr T operator()(absVector<T> &v)
			{
				//double t = 0;
				//for(unsigned int i = 0; i < v.dim(); ++i)
				//	t += pow(v[i], p);
				//return pow(t, 1/p);
				return pow(this->operator()(v, v.dim() - 1), 1/p);
			}

		private:
			double p;

			constexpr T operator()(absVector<T> &v, unsigned int dim){return ((dim)?(this->operator()(v, dim - 1) + pow(v[dim], p)):(pow(v[dim], p)));}
		};

		template<class T>
		class supNorm
			:absNorm<T>
		{
		public:
			absNorm<T> *Copy(){return new supNorm;}

			constexpr T operator()(absVector<T> &v)
			{
				double t = 0;
				for(unsigned int i = 0; i < v.Dim(); ++i)
					t = ((t > v[i])?(t):(v[i]));
				return t;
			}
		};
	}
}

#endif
