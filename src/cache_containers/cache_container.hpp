#pragma once

#include <string>
#include <unordered_map>
#include <memory>



class cache_container
{
    private:
        std::unordered_map<std::string, long long> cache;

    public:
        void put(const std::string& key, long long result);
        void put(const std::string& key, int status);
        bool has(const std::string& key) const;
        long long get(const std::string& key) const;
       
        

    
};