#include <iostream>
#include <random>
#include <cstdint>
#include <ctime>
#include "general.h"
#include "buffer.h"

using namespace ZNAC;

int IsInclude(Array<uint64_t> &a, uint64_t target)
{
	for(unsigned int i = 0; i < a.Used; ++i)
		if(a[i] == target)
			return i;
	return -1;
}

int main()
{
	std::mt19937 rnd(1);
	unsigned int num = 10000000;
	Array<uint64_t> a;
	//bTree<uint64_t> a;

	clock_t t0 = clock();
	for(unsigned int i = 0; i < num; ++i)
		a.Add(i, rnd());
		//a.Add(rnd());
	clock_t t1 = clock();

	int n;
	//const uint64_t *n;
	uint64_t N;
	std::cout << "construct time:" << (t1 - t0)/(double)CLOCKS_PER_SEC << "(s)\n" << std::endl;
	clock_t t2 = clock();
	for(unsigned int i = 0; i < num; ++i)
		if((n = IsInclude(a, N = rnd())) > -1)
		//if((n = a.Get(N = rnd())) != nullptr)
			std::cout << "find out index: " << n << "\ta[" << n << "]: " << a[n] << ":N = " << N << "\n";
			;//std::cout << "find out index: " << n << "\ta[" << n << "]: " << *n << ":N = " << N << "\n";
	clock_t t3 = clock();
	std::cout << "search time   :" << (t3 - t2)/(double)CLOCKS_PER_SEC << "(s)\n";
}
