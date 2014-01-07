#include "Real.h"

using namespace ZNAC::ODE;

Real::Real():buf(0), length(0){}
Real::Real(unsigned int length):buf(new double[length]), length(length){}
Real::~Real(){delete [] buf;}

unsigned int Real::Range(){return length;}

Domain *Real::Clone(){return new Real(length);}

double &Real::operator[](unsigned int i)
{
	return buf[i];
}
