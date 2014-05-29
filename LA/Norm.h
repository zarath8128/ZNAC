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
		class lNorm
		{
		public:
			constexpr lNorm(double p):p(p){}

			T operator()(const IVector<T> &v) const
			{
				T tmp = 0;
				for(unsigned int i = 0; i < v.N(); ++i)
					tmp += pow(ABS(v[i]), p);
				return pow(tmp, 1/p);
			}

			template<class VALID_INDEX>
			T operator ()(const IVector<T> &v, const VALID_INDEX &valid)const
			{
				T tmp = 0;
				for(auto &i : valid)
					tmp += pow(ABS(v[i]), p);
				return pow(tmp, 1/p);
			}

		private:
			double p;
		};

		template<class T>
		class supNorm
		{
		public:
			T operator ()(const IVector<T> &v)const
			{
				T tmp = 0;
				for(unsigned int i = 0; i < v.N(); ++i)
					tmp = tmp > ABS(v[i]) ? tmp : ABS(v[i]);
				return tmp;
			}

			template<class VALID_INDEX>
			T operator()(const IVector<T> &v, const VALID_INDEX &valid) const
			{
				T tmp = 0;
				for(auto &i : valid)
					tmp = tmp > ABS(v[i]) ? tmp : ABS(v[i]);
				return tmp;
			}
		};
	}
}

#endif
