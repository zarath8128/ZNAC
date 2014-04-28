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
		{
		public:
			virtual ~INorm(){}
			virtual T operator()(const IVector<T>&v)const = 0;
		};

		template<class T>
		class lNorm
			:public INorm<T>
		{
		public:
			lNorm(double p):p(p){}

			T operator ()(const IVector<T> &v)const
			{
				T tmp = 0;
				for(unsigned int i = 0; i < v.N(); ++i)
					tmp += pow(ABS(v[i]), p);
				return pow(tmp, 1/p);
			}

		private:
			double p;
		};

		template<class T>
		class supNorm
			:public INorm<T>
		{
		public:
			T operator ()(const IVector<T> &v)const
			{
				T tmp = 0;
				for(unsigned int i = 0; i < v.N(); ++i)
					tmp = tmp > ABS(v[i]) ? tmp : ABS(v[i]);
				return tmp;
			}
		};
	}
}

#endif
