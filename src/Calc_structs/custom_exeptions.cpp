#include "custom_exeptions.hpp"


Division_by_zero_exception::Division_by_zero_exception(const std::string& error) : std::runtime_error(error) {};

Overflow_exception::Overflow_exception(const std::string& error) : std::runtime_error(error) {};
Not_int_result_exception::Not_int_result_exception(const std::string& error) : std::runtime_error(error) {};
Negative_factorial_base_exception::Negative_factorial_base_exception(const std::string& error): std::runtime_error(error) {};