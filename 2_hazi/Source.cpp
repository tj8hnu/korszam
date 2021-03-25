#include "Header.h"
#include <iostream>
#include <cmath>

int main()
{
	Vector2<double> v1{}, v2{};
	double lambda;
	std::cout << "Enter vector 1:\n";
	std::cin >> v1;
	std::cout << "Enter vector 2:\n";
	std::cin >> v2;
	std::cout << "Enter scalar:\n";
	std::cin >> lambda;

	std::cout << "The sum of the two vectors is:\n" << v1 + v2 << "\n";
	std::cout << "The difference of the two vectors is:\n" << v1 - v2 << "\n";
	std::cout << "The scalar product of the two vectors is:\n" << dot(v1, v2) << "\n";
	std::cout << "The product of the first vector and the scalar is:\n" << v1*lambda << "\n";
	std::cout << "The product of the scalar and the first vector is:\n" << lambda*v1 << "\n";
	std::cout << "The first vector divided by the scalar is:\n" << v1/lambda << "\n";
	std::cout << "The length of the first vector is:\n" << length(v1) << "\n";
	std::cout << "The squarelength of the first vector is:\n" << sqlength(v1) << "\n";
	std::cout << "The normalized version of the first vector is:\n" << normalize(v1) << "\n";
	
	v2 *= 2.0;
	v2 += v1;
	v2 /= 2.0;
	v2 -= v1;
	
	std::cout << "And this is what we got if we multiply the second vector by two, then add the first vector to it, then divide it by two, and finally deduct the firt vector from it:\n" << v2 << "\n";
	
	return 0;
}