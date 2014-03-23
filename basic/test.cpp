#include <iostream>
#include "general.h"

using namespace ZNAC;

int main()
{
	ReadBuffer<Vector2> b;
	b << Vector2(2, 3);
	b << Vector2(3, 5.5);
	b << Vector2(1.2, 2.3);
	for(unsigned int i = 0; i < b.Used; ++i)
		std::cout << b[i].x << "\t" << b[i].y << std::endl;
}
