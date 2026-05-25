#include "Printer.hpp"
#include "Logger.hpp"


void Printer::printResult(long long result)
{
    calc_logger::instance().info("Result is " + std::to_string(result));
    calc_logger::instance().info("Result printed");
}

void Printer::printError(const std::string& ermsg)
{
     calc_logger::instance().error("Error: " +ermsg);
    calc_logger::instance().error("Error printed");
}