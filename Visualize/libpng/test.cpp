#include "PNGWriter.h"
#include <cstdlib>

using namespace ZNAC::libpng;
int main()
{
	//PNGWriter png("test.png");
	unsigned int width = 120, height = 60;
	unsigned char *image[height];
	double colors[3*width*height];

	for(unsigned int i = 0; i < height; ++i)
	{
		image[i] = (unsigned char *)malloc(4*width*sizeof(unsigned char));
		for(unsigned int j = 0; j < width; ++j)
		{
			image[i][4*j + 0] = 255;
			image[i][4*j + 1] = 0;
			image[i][4*j + 2] = 0;
			image[i][4*j + 3] = 255;
			colors[i*width + j] = 0.5;
			colors[width*height + i*width + j] = 0.1;
			colors[2*width*height + i*width + j] = 0.2;
		}
	}
	printf("error code:%d\n", PNGWrite("red_image.png", image, width, height));
	draw_png(1, width, height, 0, 0, colors, colors + width*height, colors + 2*width*height, "test", "./");

	return 0;
}
