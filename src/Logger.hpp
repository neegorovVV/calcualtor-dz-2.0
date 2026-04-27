#pragma once

#include <string>
#include <memory>
#include <spdlog/spdlog.h>


class calc_logger
{
    private:
        calc_logger();
        std::shared_ptr<spdlog::logger> logger_;


    public:

        static calc_logger& instance();

        void info(const std::string& msg);
        void warn(const std::string& msg);
        void error(const std::string& msg);

        calc_logger(const calc_logger&) = delete;
        calc_logger& operator=(const calc_logger&) = delete;

        

};