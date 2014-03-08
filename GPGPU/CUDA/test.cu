#include <iostream>
#include <cuda.h>

int main()
{
	cudaError_t err;
	double *v;
	int c;
	cudaGetDeviceCount(&c);
	std::cout << c << std::endl;
	err = cudaMalloc(&v, 100*sizeof(double));
	std::cout << cudaGetErrorString(err) << std::endl;
	err = cudaFree(v);
	std::cout << cudaGetErrorString(err) << std::endl;
}
