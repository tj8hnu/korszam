// 3_hazi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iterator>
using namespace std;

//Functions
double shape(double x, double F, double q, double a, double h) {
	double val = cosh(q / F * x) - cosh(q / 2 * a / F);
	return F / q * val + h;
}

double der_shape(double x, double F, double q, double a, double h, double t)
{
	double val1 = 34 * (shape(x - 2 * t, F, q, a, h) - shape(x + 2 * t, F, q, a, h));
	double val2 = 64 * (shape(x + t, F, q, a, h) - shape(x - t, F, q, a, h));
	double val3 = shape(x + 4 * t, F, q, a, h) - shape(x - 4 * t, F, q, a, h);
	return abs((val1 + val2 + val3) / (360 * t));
}

double cent_int(double min, double max, int n, double F, double q, double a, double h, double t)
{
	double d = (max - min) / n;
	double val = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		val += der_shape(min + d / 2 + i * d, F, q, a, h, t) * d;
	}
	return val;
}

double trap_int(double min, double max, int n, double F, double q, double a, double h, double t)
{
	double d = (max - min) / n;
	double val = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		val += 0.5*(der_shape(min + i * d, F, q, a, h, t) + der_shape(min + (i+1) * d, F, q, a, h, t)) * d;
	}
	return val;
}

double simp_int(double min, double max, int n, double F, double q, double a, double h, double t) // https://stackoverflow.com/questions/60005533/composite-simpsons-rule-in-c
{
	double d = (max - min) / n;

	// Internal sample points, there should be n - 1 of them
	double sum_odds = 0.0;
	for (int i = 1; i < n; i += 2)
	{
		sum_odds += der_shape(min + i * d, F, q, a, h, t);
	}
	double sum_evens = 0.0;
	for (int i = 2; i < n; i += 2)
	{
		int n_simp = 100;
		sum_evens += der_shape(min + i * d, F, q, a, h, t);
	}

	return (der_shape(min, F, q, a, h, t) + der_shape(max, F, q, a, h, t) + 2 * sum_evens + 4 * sum_odds) * d/3;
}


int main()
{
	//Numerical parameters
	double F = 900.0;
	double q = 1.8;
	double a = 200.0;
	double h = 35.0;



	double t = sqrt(DBL_EPSILON);
	int n_cent = 100;
	int n_trap = 100;
	int n_simp = 100;



	std::vector<double> data = {cent_int(0, a, n_cent, F, q, a, h, t), trap_int(0, a, n_trap, F, q, a, h, t), simp_int(0, a, n_simp, F, q, a, h, t)};


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
