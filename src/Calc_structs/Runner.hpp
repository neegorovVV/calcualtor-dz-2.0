#pragma once
#include <string>

#include "Connection_and_result.hpp"
#include "cache_container.hpp"
#include "/home/test182/calculator/src/TCP_server/TCP_server.hpp"

class Runner
{
   private:
    cache_container cache_result_container;
    cache_container cache_status_container;
    PostgresConnection data_base;
    TCP_Server server; 

   public:
    Runner();
    ~Runner() = default;
    Runner(const Runner& other) = delete;
    Runner& operator=(const Runner& other) = delete;
    Runner(Runner&& other) = delete;
    Runner& operator=(Runner&& other) = delete;
    void Run();
    void heat_cache();
    void insert_to_db(int first_value, int second_value, std::string operation_value,
                      long long result_value, int status_value);
    void insert_to_db(int first_value, int second_value, std::string operation_value,
                      const int result_value, int status_value);
    int get_status() const;
    std::string handle_request(const std::string& data); 
    void stop();
};