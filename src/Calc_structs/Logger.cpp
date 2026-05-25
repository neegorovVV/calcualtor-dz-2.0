#include "Logger.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

calc_logger& calc_logger::instance() 
{
    static calc_logger instance;
    return instance;
}

calc_logger::~calc_logger()
{
    spdlog::drop("console");
}

calc_logger::calc_logger() 
{
    auto console = spdlog::stdout_color_mt("console");
    logger_ = console.get();
    logger_->set_level(spdlog::level::info);
}


void calc_logger::info(const std::string& msg) 
{
    logger_->info(msg);
}

void calc_logger::warn(const std::string& msg) 
{
    logger_->warn(msg);
}

void calc_logger::error(const std::string& msg) 
{
    logger_->error(msg);
}