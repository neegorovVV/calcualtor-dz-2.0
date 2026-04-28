#include "Runner.hpp"
#include "Parser.hpp"
#include "Logger.hpp"
#include "Calculator.hpp"
#include "Printer.hpp"
#include <stdexcept>



void Runner::Run(int argc, char* argv[])
{   
    if (argc != 2)
    {
        calc_logger::instance().error("Usage: ./calc_oop '<json>'");
        calc_logger::instance().info("Usage example: ./calc_oop '{\"first\":10,\"second\":5,\"op\":\"+\"}'");
        return;
    }

    std::string jsonString = argv[1];
    calc_logger::instance().info("Application started with JSON: " + jsonString);

    try
    {
        Parser parser;
        parser.parse(jsonString);
        
        int first = parser.getFirst();
        int second = parser.getSecond();
        std::string operation = parser.getOperation();
        
        calc_logger::instance().info("Parsed: first=" + std::to_string(first) +  ", second=" + std::to_string(second) +   ", op=" + operation);

        Calculator calc;
        long long result = 0;

         if (operation == "+") {
            result = calc.add(first, second);
        } else if (operation == "-") {
            result = calc.subtract(first, second);
        } else if (operation == "*") {
            result = calc.multiply(first, second);
        } else if (operation == "/") {
            result = calc.divide(first, second);
        } else if (operation == "^") {
            result = calc.exponentiation(first, second);
        } else if (operation == "!") {
            result = calc.factorial(first);
        } else {
            throw std::runtime_error("Unknown operation: " + operation);
        }

             
        calc_logger::instance().info("Calculation completed, result=" + std::to_string(result));
        
        Printer printer;
        printer.printResult(result);
    }

    catch (const std::exception& e) 
    {
        calc_logger::instance().error(e.what());
        Printer printer;
        printer.printError(e.what());
    }
    
    calc_logger::instance().info("Application finished");
}
     
