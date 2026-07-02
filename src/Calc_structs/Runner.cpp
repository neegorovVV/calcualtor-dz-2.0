#include "Runner.hpp"

#include <stdexcept>
#include <string>

#include "Calculator.hpp"
#include "Logger.hpp"
#include "Parser.hpp"
#include "Printer.hpp"
#include "cache_container.hpp"

void Runner::heat_cache()
{
    auto result = data_base.execute(
        "SELECT first_operand, second_operand, operation, result, status FROM calculation_history "
        "WHERE status IN (0, 1, 2, 3, 4)");
    calc_logger::instance().info(" \t Runner is heating cache ");

    for (int i = 0; i < result.get_rows(); i++)
    {
        try
        {
            int first = std::stoi(result.get_value(i, 0));
            int second = std::stoi(result.get_value(i, 1));
            std::string op = result.get_value(i, 2);

            std::string temp_cache_key;
            if (op == "+" || op == "*")
            {
                int a = std::min(first, second);
                int b = std::max(first, second);
                temp_cache_key = std::to_string(a) + op + std::to_string(b);
            }
            else
            {
                temp_cache_key = std::to_string(first) + op + std::to_string(second);
            }

            long long temp_result = std::stoll(result.get_value(i, 3));
            int temp_status = std::stoi(result.get_value(i, 4));

            cache_result_container.put(temp_cache_key, temp_result);
            cache_status_container.put(temp_cache_key, temp_status);

            calc_logger::instance().info(
                "# " + std::to_string(i) + " Cache Key Value: " + temp_cache_key +
                " Result: " + std::to_string(temp_result) +
                " Has put to Cache Conteiner From Data Base With Status: " +
                std::to_string(temp_status));
        }
        catch (const std::exception& e)
        {
            calc_logger::instance().error(" \t Heating cache is not done succsefully.");
        }
    }
    calc_logger::instance().info(" \t Heating cache is done succsefully.");
}

Runner::Runner()
    : data_base("localhost", "5432", "calculator_db", "calc_user", "calc_pass"),
      server([this](const std::string& data) -> std::string { return this->handle_request(data); })
{
    heat_cache();
}

void Runner::insert_to_db(int first_value, int second_value, std::string operation_value,
                          long long result_value, int status_value)
{
    data_base.execute(
        "INSERT INTO calculation_history "
        "(first_operand, second_operand, operation, result, status) VALUES (" +
        std::to_string(first_value) + ", " + std::to_string(second_value) + ", '" +
        operation_value + "', " + std::to_string(result_value) + ", " +
        std::to_string(status_value) + ")");
}

void Runner::insert_to_db(int first_value, int second_value, std::string operation_value,
                          const int result_value, int status_value)
{
    data_base.execute(
        "INSERT INTO calculation_history "
        "(first_operand, second_operand, operation, result, status) VALUES (" +
        std::to_string(first_value) + ", " + std::to_string(second_value) + ", '" +
        operation_value + "', " + std::to_string(result_value) + ", " +
        std::to_string(status_value) + ")");
}

std::string Runner::handle_request(const std::string& jsonString)
{
    int first;
    int second;
    std::string operation;

    try
    {
        Parser parser;
        parser.parse(jsonString);

        int status = 0;
        first = parser.getFirst();
        second = parser.getSecond();
        operation = parser.getOperation();
        std::string cache_key = parser.get_cache_string();

        Calculator calc;
        long long result = 0;

        calc_logger::instance().info("Parsed: first=" + std::to_string(first) +
                                     ", second=" + std::to_string(second) + ", op=" + operation);

        if (cache_result_container.has(cache_key))

        {
            result = cache_result_container.get(cache_key);
            status = cache_status_container.get(cache_key);

            if (result == -4040404 && status == 1 || result == -4040404 && status == 2 ||
                result == -4040404 && status == 3 || result == -4040404 && status == 4)
            {
                calc_logger::instance().info(
                    "This Incoming Arguments Already Existing In DB OR CACHE Container. So "
                    "Calculating Is Skipped.");
                calc_logger::instance().error("Result from cache is NONE due to calculation error");
                calc_logger::instance().error("RESULT IS NONE");
                return "ERROR: Calculation error from cache";
            }

            calc_logger::instance().info(
                "This Incoming Arguments Already Existing In DB OR CACHE Container. So Calculating "
                "Is Skipped. Result from cache: " +
                std::to_string(result));
            return std::to_string(result);
        }
        else
        {
            if (operation == "+")
                result = calc.add(first, second);
            else if (operation == "-")
                result = calc.subtract(first, second);
            else if (operation == "*")
                result = calc.multiply(first, second);
            else if (operation == "/")
                result = calc.divide(first, second);
            else if (operation == "^")
                result = calc.exponentiation(first, second);
            else if (operation == "!")
                result = calc.factorial(first);
            else
                throw std::runtime_error("Unknown operation: " + operation);

            cache_result_container.put(cache_key, result);
            calc_logger::instance().info("Calculation completed, result=" + std::to_string(result) +
                                         " With status: " + std::to_string(status));

            insert_to_db(first, second, operation, result, status);

            calc_logger::instance().info("Result has put to DB");
        }

        Printer printer;
        printer.printResult(result);
        return std::to_string(result);
    }

    catch (const Overflow_exception& e)
    {
        calc_logger::instance().info("Calculation failed, Result with error has put to DB.");
        int error_status = 2;
        const int ERROR_RESULT = -4040404;
        insert_to_db(first, second, operation, ERROR_RESULT, error_status);

        Printer printer;
        printer.printError(e.what());
        return "ERROR: " + std::string(e.what());
    }
    catch (const Division_by_zero_exception& e)
    {
        calc_logger::instance().info("Calculation failed, Result with error has put to DB.");
        int error_status = 1;
        const int ERROR_RESULT = -4040404;
        insert_to_db(first, second, operation, ERROR_RESULT, error_status);

        Printer printer;
        printer.printError(e.what());
        return "ERROR: " + std::string(e.what());
    }
    catch (const Not_int_result_exception& e)
    {
        calc_logger::instance().info("Calculation failed, Result with error has put to DB.");
        int error_status = 3;
        const int ERROR_RESULT = -4040404;
        insert_to_db(first, second, operation, ERROR_RESULT, error_status);

        Printer printer;
        printer.printError(e.what());
        return "ERROR: " + std::string(e.what());
    }
    catch (const Negative_factorial_base_exception& e)
    {
        calc_logger::instance().info("Calculation failed, Result with error has put to DB.");
        int error_status = 4;
        const int ERROR_RESULT = -4040404;
        insert_to_db(first, second, operation, ERROR_RESULT, error_status);

        Printer printer;
        printer.printError(e.what());
        return "ERROR: " + std::string(e.what());
    }
    catch (const std::exception& e)
    {
        calc_logger::instance().error("Calculation failed.");
        Printer printer;
        printer.printError(e.what());
        return "ERROR: " + std::string(e.what());
    }

    calc_logger::instance().info("Application finished");
}

void Runner::stop()
{
    server.stop();
}
void Runner::Run()
{
    calc_logger::instance().info("TCP server started succesfully ");

    server.run();

    // \\\\\handle_request\\\;

    // int first;
    // int second;
    // std::string operation;

    // try
    // {
    //     Parser parser;
    //     parser.parse(jsonString);

    //     int status = 0;
    //     first = parser.getFirst();
    //     second = parser.getSecond();
    //     operation = parser.getOperation();
    //     std::string cache_key = parser.get_cache_string();

    //     Calculator calc;
    //     long long result = 0;

    //     calc_logger::instance().info("Parsed: first=" + std::to_string(first) +
    //                                  ", second=" + std::to_string(second) + ", op=" + operation);

    //     if (cache_result_container.has(cache_key))

    //     {
    //         result = cache_result_container.get(cache_key);
    //         status = cache_status_container.get(cache_key);

    //         if (result == -4040404 && status == 1 || result == -4040404 && status == 2 ||
    //             result == -4040404 && status == 3 || result == -4040404 && status == 4)
    //         {
    //             calc_logger::instance().info(
    //                 "This Incoming Arguments Already Existing In DB OR CACHE Container. So "
    //                 "Calculating Is Skipped.");
    //             calc_logger::instance().error("Result from cache is NONE due to calculation
    //             error"); calc_logger::instance().error("RESULT IS NONE"); return;
    //         }

    //         calc_logger::instance().info(
    //             "This Incoming Arguments Already Existing In DB OR CACHE Container. So
    //             Calculating " "Is Skipped. Result from cache: " + std::to_string(result));
    //         return;
    //     }
    //     else
    //     {
    //         if (operation == "+")
    //             result = calc.add(first, second);
    //         else if (operation == "-")
    //             result = calc.subtract(first, second);
    //         else if (operation == "*")
    //             result = calc.multiply(first, second);
    //         else if (operation == "/")
    //             result = calc.divide(first, second);
    //         else if (operation == "^")
    //             result = calc.exponentiation(first, second);
    //         else if (operation == "!")
    //             result = calc.factorial(first);
    //         else
    //             throw std::runtime_error("Unknown operation: " + operation);

    //         cache_result_container.put(cache_key, result);
    //         calc_logger::instance().info("Calculation completed, result=" +
    //         std::to_string(result) +
    //                                      " With status: " + std::to_string(status));

    //         insert_to_db(first, second, operation, result, status);

    //         calc_logger::instance().info("Result has put to DB");
    //     }

    //     Printer printer;
    //     printer.printResult(result);
}

