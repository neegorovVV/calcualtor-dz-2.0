#include <gtest/gtest.h>
#include "../src/Calculator.hpp"

TEST(CalculatorTest, AddPositive) 
{
    Calculator calc;
    EXPECT_EQ(calc.add(10, 5), 15);
}

TEST(CalculatorTest, AddNegative)
{
    Calculator calc;
    EXPECT_EQ(calc.add(-10,-5), -15);
}

TEST(CalculatorTest, AddOverflowCheck)
{
    Calculator calc;
    EXPECT_THROW(calc.add(INT_MAX, 1), std::runtime_error);
}

TEST(CalculatorTest, SubtractPositive) 
{
    Calculator calc;
    EXPECT_EQ(calc.subtract(10, 5), 5);
}

TEST(CalculatorTest, SubtractNegative) 
{
    Calculator calc;
    EXPECT_EQ(calc.subtract(10, -5), 15);
}

TEST(CalculatorTest, SubtractOverflowCheckMax) 
{
    Calculator calc;
    EXPECT_THROW(calc.subtract(INT_MAX, -1), std::runtime_error);
}

TEST(CalculatorTest, SubtractOverflowCheckMin) 
{
    Calculator calc;
    EXPECT_THROW(calc.subtract(INT_MIN, 1), std::runtime_error);
}

TEST(CalculatorTest, MultiplyPositive) 
{
    Calculator calc;
    EXPECT_EQ(calc.multiply(10, 5), 50);
}

TEST(CalculatorTest, MultiplyNegative) 
{
    Calculator calc;
    EXPECT_EQ(calc.multiply(-10, -5), 50);
}


TEST(CalculatorTest, MultiplyOverflowCheckMax) 
{
    Calculator calc;
    EXPECT_THROW(calc.multiply(INT_MIN, -1), std::runtime_error);
}

TEST(CalculatorTest, DividePositive) 
{
    Calculator calc;
    EXPECT_EQ(calc.divide(10, 5), 2);
}

TEST(CalculatorTest, DivideNegative) 
{
    Calculator calc;
    EXPECT_EQ(calc.divide(-10, -5), 2);
}

TEST(CalculatorTest, DivideZero) 
{
    Calculator calc;
    EXPECT_THROW(calc.divide(-10, 0), std::runtime_error);
}

TEST(CalculatorTest, DivideOverflowCheckMax) 
{
    Calculator calc;
    EXPECT_THROW(calc.divide(INT_MIN, -1), std::runtime_error);
}

TEST(CalculatorTest, ExponentiationOverflowCheck) 
{
    Calculator calc;
    EXPECT_THROW(calc.exponentiation(INT_MAX, 20), std::runtime_error);
}

TEST(CalculatorTest, NegativeExponentiation) 
{
    Calculator calc;
    EXPECT_THROW(calc.exponentiation(10, -2), std::runtime_error);
}

TEST(CalculatorTest, ZeroBaseAndZeroExp) 
{
    Calculator calc;
    EXPECT_EQ(calc.exponentiation(0, 0), 1);
}

TEST(CalculatorTest, ZeroBase) 
{
    Calculator calc;
    EXPECT_EQ(calc.exponentiation(0, 2), 0);
}

TEST(CalculatorTest, PositiveBaseExponentiation) 
{
    Calculator calc;
    EXPECT_EQ(calc.exponentiation(10, 2), 100);
}

TEST(CalculatorTest, NegativeBaseExponentiation) 
{
    Calculator calc;
    EXPECT_EQ(calc.exponentiation(-10, 2), 100);
}

TEST(CalculatorTest, Factorial) 
{
    Calculator calc;
    EXPECT_EQ(calc.factorial(5), 120);
}

TEST(CalculatorTest, FactorialOne) 
{
    Calculator calc;
    EXPECT_EQ(calc.factorial(1), 1);
}

TEST(CalculatorTest, FactorialZero)
{
    Calculator calc;
    EXPECT_EQ(calc.factorial(0), 1);
}

TEST(CalculatorTest, NegativeBaseFactorial) 
{
    Calculator calc;
    EXPECT_THROW(calc.factorial(-5), std::runtime_error);
}

TEST(CalculatorTest, FactorialOverflow) {
    Calculator calc;
    EXPECT_THROW(calc.factorial(30), std::runtime_error);
}