#pragma once

#include <string>

class Printer
{
   private:
   public:
    void printResult(long long result);
    void printError(const std::string& ErrorMsg);

    Printer() = default;
    ~Printer() = default;
    Printer(const Printer& other) = delete;
    Printer& operator=(const Printer& other) = delete;
    Printer(Printer&& other) = delete;
    Printer& operator=(Printer&& other) = delete;
};