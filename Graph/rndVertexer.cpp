#include "Graph.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char** argv)
{
	if(argc != 3)
	{
invalid_data:
		std::cerr << "invalid data.\n";
		std::cerr << argv[0] << " is requwired 2 argument.\nuse below.\n";
		std::cerr << argv[0] << " point_num file_path\n";
		return 1;
	}

	unsigned int point_num;
	if(sscanf(argv[1], "%d", &point_num) == EOF)
		goto invalid_data;
	char path[256];
	if(sscanf(argv[2], "%s", path) == EOF)
		goto invalid_data;

	std::cout << "point_num :\t" << point_num << std::endl;
	std::cout << "file_path :\t" << path << std::endl;

	srand(time(nullptr));

	ZNAC::Graph::Vertex<ZNAC::Vector<2>> v;
	ZNAC::Vector<2> w;

	for(unsigned int i = 0; i < point_num; ++i)
	{
		w[0] = rand()/(double)RAND_MAX;
		w[1] = rand()/(double)RAND_MAX;

		v << w;
	}
	v.WriteOut(path);
}
