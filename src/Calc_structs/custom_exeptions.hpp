#pragma once

#include <stdexcept>
#include <string>

class Division_by_zero_exception : public std::runtime_error
{
    public:
        explicit Division_by_zero_exception(const std::string& error);
};

class Overflow_exception : public std::runtime_error
{
    public:
        explicit Overflow_exception(const std::string& error);
};

class Not_int_result_exception : public std::runtime_error
{
    public:
        explicit Not_int_result_exception(const std::string& error);
};

class Negative_factorial_base_exception : public std::runtime_error
{
    public:
        explicit Negative_factorial_base_exception(const std::string& error);
};