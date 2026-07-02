#pragma once

#include <climits>
#include <math-lib-oop.hpp>
#include <stdexcept>
#include <string>

class Calculator
{
   private:
   public:
    long long add(int a, int b);

    long long subtract(int a, int b);

    long long multiply(int a, int b);

    long long divide(int a, int b);

    long long exponentiation(int base, int exp);

    long long factorial(int a);

    Calculator() = default;
    ~Calculator() = default;
    Calculator(const Calculator& other) = delete;
    Calculator& operator=(const Calculator& other) = delete;
    Calculator(Calculator&& other) = delete;
    Calculator& operator=(Calculator&& other) = delete;
};