#ifndef ZARATH_ZNAC_ODE_REAL_H
#define ZARATH_ZNAC_ODE_REAL_H

#include "ODE.h"

namespace ZNAC
{
	namespace ODE
	{
		class Real
			:public Domain
		{
		public:
			Real();
			Real(unsigned int length);
			~Real();
			unsigned int Range();
			Domain *Clone();
			double &operator[](unsigned int i);
		private:
			const unsigned int length;
			double *buf;
		};
	}
}

#endif
