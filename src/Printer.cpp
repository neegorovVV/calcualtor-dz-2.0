#include "Printer.hpp"
#include "Logger.hpp"
#include<iostream>

void Printer::printResult(long long result)
{
    std::cout << "Result: " << result << std::endl;
    calc_logger::instance().info("Result printed: " + std::to_string(result));
}

void Printer::printError(const std::string& ermsg)
{
    std::cout << "Error: " << ermsg << std::endl;
    calc_logger::instance().error("Error printed: " +ermsg);
}