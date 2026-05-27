#pragma once
#include <string>

#include "Connection_and_result.hpp"
#include "cache_container.hpp"

class Runner
{
   private:
    cache_container cache_result_container;
    cache_container cache_status_container;
    PostgresConnection data_base;

   public:
    Runner();
    void Run(int argc, char* argv[]);
    void heat_cache();
    void insert_to_db(int first_value, int second_value, std::string operation_value,
                      long long result_value, int status_value);
    void insert_to_db(int first_value, int second_value, std::string operation_value,
                      const int result_value, int status_value);
    int get_status() const;
};