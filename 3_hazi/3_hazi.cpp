// 3_hazi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iterator>
using namespace std;


//Numerical parameters
#define F 900.0
#define q 1.8
#define a 200.0
#define h 35.0



//Functions
double shape(double x)
{
	double val1 = cosh((q/F) * x);
	double val2 = cosh(q / 2 * a / F);
	double val = val1 - val2;
	return F / q * val + h;
}

double der_shape(double x, double t)
{
	double val1 = 34 * (shape(x - 2 * t) - shape(x + 2 * t));
	double val2 = 64 * (shape(x + t) - shape(x - t));
	double val3 = shape(x + 4 * t) - shape(x - 4 * t);
	return (val1 + val2 + val3) / (360 * t);
}

double int_shape(double x, double t)
{
	return sqrt(1 + pow(der_shape(x, t),2));
}

double cent_int(double min, double max, int n, double t)
{
	double d = (max - min) / n;
	double val = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		val += int_shape(min + d / 2 + i * d, t) * d;
	}
	return val;
}

double trap_int(double min, double max, int n, double t)
{
	double d = (max - min) / n;
	double val = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		val += 0.5*(int_shape(min + i * d, t) + int_shape(min + (i+1) * d, t)) * d;
	}
	return val;
}

double simp_int(double min, double max, int n, double t) // https://stackoverflow.com/questions/60005533/composite-simpsons-rule-in-c
{
	double d = (max - min) / n;

	// Internal sample points, there should be n - 1 of them
	double sum_odds = 0.0;
	for (int i = 1; i < n; i += 2)
	{
		sum_odds += int_shape(min + i * d, t);
	}
	double sum_evens = 0.0;
	for (int i = 2; i < n; i += 2)
	{
		sum_evens += int_shape(min + i * d, t);
	}

	return (int_shape(min, t) + int_shape(max, t) + 2 * sum_evens + 4 * sum_odds) * d/3;
}


int main()
{
	double t = 200.0 / 10000;
	int n_cent = 10000;
	int n_trap = 10000;
	int n_simp = 10000;


	std::vector<double> data = {cent_int(0, a, n_cent, t), trap_int(0, a, n_trap, t), simp_int(0, a, n_simp, t)};


	std::ofstream output("data.txt");
	if (output.is_open())
	{
		std::copy(data.begin(), data.end(), std::ostream_iterator<int>(output, ","));
	}
	else { std::cout << "Could not open output file\n"; }


	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
