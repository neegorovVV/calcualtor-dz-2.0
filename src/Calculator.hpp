#pragma once

#include<string>
#include<climits>
#include <stdexcept>

class Calculator
{
    private:

        int firstnum;
        int secondnum;
        std::string operation;
        long long result;

    public:


    long long add(int a, int b);


    long long subtract(int a, int b);


    long long multiply(int a, int b);


    long long divide(int a, int b);


    long long exponentiation(int base, int exp);


    long long factorial(int a);


};