#include <iostream>
#include "general.h"
#include "arrow.h"

using namespace ZNAC;

int main()
{
	int a = 10, aa = 20;
	int * b = &a, *bb = &aa;
	int * const & c = b;
	std::cout << *c << std::endl;
	b = &aa;
	*c = 100;
	std::cout << aa << std::endl;
}
