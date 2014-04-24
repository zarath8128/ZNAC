#include <iostream>

class test
{
public:
	const double &A = a;

private:
	double a;
};

int main()
{
	std::cout << sizeof(test) << std::endl;
}
