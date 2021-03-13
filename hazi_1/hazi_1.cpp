// hazi_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>


template<typename F,typename dF, typename T>
T Newton(F f, dF df, T x0, int n = 100) //by default we iterate for 100
{
    double xn = x0, temp = x0; //iterating point and temporary point
    for (int i = 1; i <= n; i++)
    {
        temp = xn - f(xn)/df(xn); //calculate the new point
        xn = temp; //get the value
    }
    return xn;
}



int main()
{
    std::cout << Newton([](double x) { return x * x - 612.0; },
        [](double x) { return 2.0 * x; }, 10.0);
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
