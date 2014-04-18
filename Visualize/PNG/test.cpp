#include "PNGWriter.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace ZNAC::Visualize;
int main()
{
	PNGWriter pw("./sample", "ttt", 100, 100);

	unsigned char *image[100], base_image[100][100][4];

	for(int i = 0; i < 100; ++i)
	{
		image[i] = (unsigned char *)base_image[i];
		for(int j = 0; j < 100; ++j)
		{
			base_image[i][j][0] = i;
			base_image[i][j][1] = 0;//100 - i + j;
			base_image[i][j][2] = 0;//100 - j + i;
			base_image[i][j][3] = i;
		}
	}

	for(int i = 0; i < 2; ++i)
		pw << image;


	return 0;
}
