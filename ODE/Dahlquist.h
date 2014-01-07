#ifndef ZARATH_ZNAC_ODE_DAHLQUIST_H
#define ZARATH_ZNAC_ODE_DAHLQUIST_H

#include "ODE.h"

namespace ZNAC
{
	namespace ODE
	{
		class Dahlquist
			:public ODE
		{
		public:
			Dahlquist(Domain &param):param(param.Clone())
			{
				for(unsigned int i = 0; i < param.Range(); ++i)
					(*this->param)[i] = param[i];
			}

			void operator()(Domain &u, Domain &du)
			{
				for(unsigned int i = 0; i < u.Range(); ++i)
					du[i] = (*param)[i]*u[i];
			}
		private:
			Domain *param;
		};
	}
}

#endif
