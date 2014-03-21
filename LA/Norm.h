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
			:public IWrapper<T*>
		{
		public:
			INorm(unsigned int dim):dim(dim){}
			virtual ~INorm(){}
			virtual operator T() = 0;
		protected:
			const unsigned int dim;
		};

		template<class T>
		class lNorm
			:public INorm<T>
		{
		public:
			lNorm(unsigned int dim, double p):INorm<T>(dim), p(p){}

			operator T()
			{
				return pow(ABS(this->operator()(this->dim - 1)), 1/p);
			}

		private:
			double p;

			constexpr T operator()(unsigned int dim){return ((dim)?(this->operator()(dim - 1) + pow(ABS(((T*&)(*this))[dim]), p)):(pow(ABS(((T*&)(*this))[dim]), p)));}
		};

		template<class T>
		class supNorm
			:public INorm<T>
		{
		public:
			operator T()
			{
				return this->operator()(this->dim - 1);
			}

		private:
			constexpr T operator()(unsigned int dim)
			{
				return ((dim)?(MAX(ABS(this->buf[dim]), this->operator()(dim - 1))):(ABS(this->buf[dim])));
			}
		};
	}
}

#endif
