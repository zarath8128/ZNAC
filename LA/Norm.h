#ifndef ZARATH_ZNAC_LA_NORM_H
#define ZARATH_ZNAC_LA_NORM_H

#include "Vector.h"
#include "../basic/general.h"
#include <cmath>

namespace ZNAC
{
	namespace LA
	{
		template<class T>
		class INorm
			:public IClonable<INorm<T>>
		{
		public:
			virtual ~INorm(){}
			constexpr virtual T operator()(Vector<T> &v) = 0;
			constexpr virtual INorm<T> *Clone() = 0;
		};

		template<class T>
		class lNorm
			:public INorm<T>
		{
		public:
			lNorm(double p):p(p){}

			constexpr INorm<T> *Clone(){return new lNorm(p);}

			constexpr T operator()(Vector<T> &v)
			{
				return pow(ABS(this->operator()(v, v.dim() - 1)), 1/p);
			}

		private:
			double p;

			constexpr T operator()(Vector<T> &v, unsigned int dim){return ((dim)?(this->operator()(v, dim - 1) + pow(ABS(v[dim]), p)):(pow(ABS(v[dim]), p)));}
		};

		template<class T>
		class supNorm
			:public INorm<T>
		{
		public:
			constexpr INorm<T> *Clone(){return new supNorm;}

			constexpr T operator()(Vector<T> &v)
			{
				return this->operator()(v, v.dim() - 1);
			}

		private:
			constexpr T operator()(Vector<T> &v, unsigned int dim)
			{
				return ((dim)?(MAX(ABS(v[dim]), this->operator()(v, dim - 1))):(ABS(v[dim])));
			}
		};
	}
}

#endif
