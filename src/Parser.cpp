#include "Parser.hpp"
#include <nlohmann/json.hpp>
#include "Logger.hpp"

using json = nlohmann::json;

void Parser::parse(const std::string& jsonString)
{
    try
    { 
        json data = json::parse(jsonString);

        first = data["first"];

        if (data.contains("second")) 
            second = data["second"];
        else 
            second = 0;  // значение по умолчанию
        
        
        operation = data["op"];

        calc_logger::instance().info("JSON parsed correctly");
    }

    catch(const json::parse_error& e)
    {
        calc_logger::instance().error("JSON parsing error " + std::string(e.what()));
        throw;
    }
}



    int Parser::getFirst() const 
    {
        return first;
    }
    int Parser::getSecond() const 
    {
        return second;
    }

    std::string Parser::getOperation() const 
    {
        return operation;
    }
