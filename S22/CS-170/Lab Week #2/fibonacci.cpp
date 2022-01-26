
/*!*****************************************************************************
\file    fibonacci.cpp
\author  Anthon Reid
\par     DP email:  anthon.reid@digipen.edu
\par     Course: CS120
\par     lab week #2
\date    01-14-2022

\brief
  This program takes an interger and geretates fibonacci series.

  - fibonacci          
      Generates the fibonacci series.
*******************************************************************************/
#include <iostream> // cout
#include <iomanip> 
#include <cstdlib>  // atoi


void fibonacci(int max)
{

    int i;
    int fibonacci_number[70];
    int Xn_1 = 1;
    int Xn_2 = 0;
    int Xn = 0;
    double fibonacci_quotient = 0;

    for(i = 0; i < max; i++)
    {
        fibonacci_number[i] = 0;
    }

    std::cout << "           Fibonacci        Fibonacci\n";
    std::cout <<" N           number          quotient\n";
    std::cout <<"-------------------------------------\n";

    for (i = 0; i <= max; i++)
    {   
        if (i == 0 || i == 1) 
        {
            fibonacci_number[i] = i;
            std::cout << std::setw(2) << i << 
            std::setw(14) << fibonacci_number[i] <<
            std::setw(21) << "N/A" << "\n";
        }
        else
        {
            Xn = Xn_1 + Xn_2;
            fibonacci_number[i] = Xn;
            fibonacci_quotient = (double) fibonacci_number[i] / Xn_1;
            Xn_2 = Xn_1;
            Xn_1 = Xn;
            std::cout << std::setw(2) << i <<
            std::setw(14) << fibonacci_number[i] <<
            std::setw(21) << std::showpoint << 
            std::setprecision(17) << fibonacci_quotient << "\n";;
        }

        if (i >= 46)
        {
            break;
        }
    }
}