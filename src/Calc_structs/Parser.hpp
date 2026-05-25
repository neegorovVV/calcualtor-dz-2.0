#pragma once

#include <string>
#include <algorithm>

class Parser
{
    private:
        int first = 0;
        int second = 0;
        std::string operation;
        std::string cache_string;

    public:

        void parse(const std::string& jsonstring);

        int getFirst() const;
        int getSecond() const;
        std::string getOperation() const;
        std::string get_cache_string() const;



};