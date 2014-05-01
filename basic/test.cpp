#include <iostream>
#include "general.h"

using namespace ZNAC;

int main()
{
	auto j = Index(1, 2, 3, 4, 5, 7, 565, 2, 32, 5);

	for(unsigned int i = 0; i < j.N(); ++i)
		std::cout << j[i] << std::endl;;

	return 0;
}
