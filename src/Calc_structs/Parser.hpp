#pragma once

#include <algorithm>
#include <string>

class Parser
{
   private:
    int first = 0;
    int second = 0;
    std::string operation;
    std::string cache_string;

   public:
    void parse(const std::string& jsonstring);
    Parser() = default;
    ~Parser() = default;
    Parser(const Parser& other) = delete;
    Parser& operator=(const Parser& other) = delete;
    Parser(Parser&& other) = delete;
    Parser operator=(Parser&& other) = delete;

    int getFirst() const;
    int getSecond() const;
    std::string getOperation() const;
    std::string get_cache_string() const;
};