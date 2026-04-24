#pragma once

#include <string>

class Parser
{
    private:
        int first = 0;
        int second = 0;
        std::string operation;

    public:

        void parse(const std::string& jsonstring);

        int getFirst() const;
        int getSecond() const;
        std::string getOperation() const;



};