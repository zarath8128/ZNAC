#include <iostream>
#include "general.h"

using namespace ZNAC;

int main()
{
	auto j = Index(3, 4, 5, 6);
	
	for(unsigned int z = 0; z < 5; ++z)
		for(unsigned int y = 0; y < 4; ++y)
			for(unsigned int x = 0; x < 3; ++x)
			{
				std::cout << j(x, y, z, 1) << std::endl;
			}

	return 0;
}
