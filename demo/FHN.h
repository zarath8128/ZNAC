#include "../LA/Vector.h"
#include "../ODE/ODE.h"

namespace ZNAC
{
	namespace ODE
	{
		class FHN
			:public ODE<double>
		{
		public:
			void operator()(IVector<double> &u, IVector<double> &du);
		private:
			unsigned int N;
		};
	}
}

