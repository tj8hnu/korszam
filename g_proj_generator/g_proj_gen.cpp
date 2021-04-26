// g_project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iterator>
using namespace std;


int main()
{
    int n = 100;
    int m = 1000;

    std::ofstream output("input.txt");
    if (output.is_open())
    {
        int a = rand() % 100;
        int b = rand() % 100;
        output << a << '\t' << b << '\t' << n << '\t' << m << '\n';
        for (int i = 0; i < m; ++i)
        {
            int c = rand() % 100;
            int d = rand() % 100;
            double len = (double)rand() / (RAND_MAX);
            output << c << '\t' << d << '\t' << len << '\n';
        }
    }
    else { std::cout << "Could not open output file\n"; }

    return 0;
}
