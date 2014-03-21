#ifndef ZARATH_ZNAC_LA_VECTOR_H
#define ZARATH_ZNAC_LA_VECTOR_H

#include "../basic/general.h"

namespace ZNAC
{
	namespace LA
	{
		template<class T = double>
		class Vector
			:public IClonable<Vector<T>>
		{
		public:
			Vector():buf(nullptr), Dim(0){}
			Vector(unsigned int Dim):buf(new T[Dim]), Dim(Dim){}
			virtual ~Vector(){delete [] buf;}

			virtual T& operator[](unsigned int i){return buf[i];}
			virtual unsigned int dim(){return Dim;}
			virtual Vector<T> *Clone(){return new Vector<T>(Dim);}
		protected:
			T *buf;
			const unsigned int Dim;
		};
	}
}

#endif
