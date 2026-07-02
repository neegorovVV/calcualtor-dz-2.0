#pragma once

#include <atomic>
#include <csignal>

#include "Logger.hpp"

class Signal_handler {
private:
    static std::atomic<bool> running;
    static void handle_signal(int sig);

public:
    Signal_handler();
    static bool is_running();
    static void stop();
};