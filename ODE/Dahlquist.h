#ifndef ZARATH_ZNAC_ODE_DAHLQUIST_H
#define ZARATH_ZNAC_ODE_DAHLQUIST_H

#include "ODE.h"

namespace ZNAC
{
	namespace ODE
	{
		template<class T>
		class Dahlquist
			:public ODE<T>
		{
		public:
			Dahlquist(LA::Vector<T> &param):param(param.Clone())
			{
				for(unsigned int i = 0; i < param.dim(); ++i)
					(*this->param)[i] = param[i];
			}

			void operator()(LA::Vector<T> &u, LA::Vector<T> &du)
			{
				for(unsigned int i = 0; i < u.dim(); ++i)
					du[i] = (*param)[i]*u[i];
			}
		private:
			LA::Vector<T> *param;
		};
	}
}

#endif
