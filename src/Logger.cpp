#include "Logger.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

calc_logger& calc_logger::instance() {
    static calc_logger instance;
    return instance;
}

calc_logger::calc_logger() {
    logger_ = spdlog::stdout_color_mt("console");
    logger_->set_level(spdlog::level::info);
}

void calc_logger::info(const std::string& msg) {
    logger_->info(msg);
}

void calc_logger::warn(const std::string& msg) {
    logger_->warn(msg);
}

void calc_logger::error(const std::string& msg) {
    logger_->error(msg);
}