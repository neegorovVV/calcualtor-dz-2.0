#include "Signal_thread.hpp"

std::atomic<bool> Signal_handler::running(true);

Signal_handler::Signal_handler() {
    running = true;
    std::signal(SIGINT, handle_signal);
    std::signal(SIGTERM, handle_signal);
}

void Signal_handler::handle_signal(int sig) {
    if (sig == SIGINT || sig == SIGTERM) {
        running = false;
        calc_logger::instance().info("Server is shutting down...");
    }
}

bool Signal_handler::is_running() {
    return running;
}

void Signal_handler::stop() {
    running = false;
}