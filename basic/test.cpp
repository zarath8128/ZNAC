#include <iostream>
#include "general.h"

int main()
{
	std::cout << ZNAC::TemplateCount<int, int, double, int, unsigned int>() << std::endl;
}
