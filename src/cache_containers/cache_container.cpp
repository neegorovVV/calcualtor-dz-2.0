
#include "cache_container.hpp"


void cache_container::put(const std::string& key, long long result)
{
    cache.insert({key,result});
}

void cache_container::put(const std::string& key, int status)
{
    cache.insert({key,status});
}

bool cache_container::has(const std::string& key) const
{
    return cache.find(key) != cache.end();
}

long long cache_container::get(const std::string& key) const
{
    return cache.at(key);
}