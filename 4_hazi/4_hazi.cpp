// 4_hazi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iterator>
using namespace std;


#define PI 3.14159265

template<typename State, typename T, typename RHS>
vector<State> solve_new(State y0, T t0, T t1, T h, RHS f)
{
    vector<State> ys;
    ys.push_back(y0);
    T t = t0;
    State y = y0;
    while (t < t1)
    {
        if (t + h > t1)
        {
            h = t1 - t;
        }
        y = y + h * f(t, y);
        t = t + h;
        ys.push_back(y);
    }
    return ys;
}

template<typename State, typename T, typename RHS>
vector<State> solve_rk4(State y0, T t0, T t1, T h, RHS f)
{
    vector<State> ys;
    ys.push_back(y0);
    T t = t0;
    State y = y0;
    while (t < t1)
    {
        if (t + h > t1)
        {
            h = t1 - t;
        }
        State k1 = f(t, y);
        State k2 = f(t + h * (T)0.5, y + (h * (T)0.5) * k1);
        State k3 = f(t + h * (T)0.5, y + (h * (T)0.5) * k2);
        State k4 = f(t + h, y + h * k3);
        y = y + (k1 + k4 + (T)2 * (k2 + k3)) * (h / (T)6);
        t = t + h;
        ys.push_back(y);
    }
    return ys;
}

template<typename State, typename T>
vector<State> solve_ana(State y0, T t0, T t1, T h)
{
    vector<State> ys;
    ys.push_back(y0);
    T t = t0;
    State y = y0;
    while (t < t1)
    {
        if (t + h > t1)
        {
            h = t1 - t;
        }
        t = t + h;
        y = tan(t);
        ys.push_back(y);
    }
    return ys;
}

auto f(double t, double y)
{
    return 1 + pow(y, 2);
}


int main()
{
    double t0 = 0.0;
    double t1 = PI / 2;
    double h = PI /20000;
    double y0 = 0;

    vector<double> newt = solve_new(y0, t0, t1, h, f);
    vector<double> rk = solve_rk4(y0, t0, t1, h, f);
    vector<double> ana = solve_ana(y0, t0, t1, h);


    std::ofstream output("data.txt");
    if (output.is_open())
    {
        for (int i = 0; i < newt.size(); ++i)
        {
            output << newt[i] << '\t' << rk[i] << '\t' << ana[i] << '\n';
        }
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
