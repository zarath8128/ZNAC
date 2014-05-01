#include <iostream>
#include "general.h"

using namespace ZNAC;

class Test
{
private:
	double dx, xoffset;
	double x_int;
public:
	Property<double, Test> x;
	unsigned int i;

	Test(double dx, double xoffset):x([](const double &x, Test* t)->double&{return t->x_int = x;}, [](Test *t)->const double&{return t->x_int = t->xoffset + t->i*t->dx;}, this),dx(dx), xoffset(xoffset), i(0){}


};

int main()
{
	Test t(0.1, 1);
	for(t.i = 0; t.i < 20; ++t.i)
		std::cout << t.x << std::endl;
	return 0;
}
