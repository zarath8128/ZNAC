#ifndef ZARATH_ZNAC_PDE_BOUNDARY_H
#define ZARATH_ZNAC_PDE_BOUNDARY_H

#include "../LA/Vector.h"

namespace ZNAC
{
	namespace PDE
	
		template<class T>
		class Boundary
		{
		public:
			
		protected:
			Vector<T> &v;
		};

		template<class T>
		class IBoundary
		{
		public:
			constexpr virtual T operator()(int index) = 0;
		};

		template<class T, unsigned int N>
		class Neumann
			:public IBoundary<T>
		{
		public:
			constexpr T operator()(int i){reutrn ((i < 0)?(-i):((i > N - 1)?(i - ):()))}

		private:
			IVector<T> &buf;
		};
	}
}

#endif
