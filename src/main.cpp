#include <chrono>
#include <thread>

#include "Logger.hpp"
#include "Runner.hpp"
#include "/home/test182/calculator/src/TCP_server/Signal_thread.hpp"

int main()
{
    try
    {
        Signal_handler sh;

        Runner runner;
        std::thread server_thread([&runner]() { runner.Run(); });
        while (Signal_handler::is_running())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        calc_logger::instance().info("Stopping server...");
        runner.stop();
        server_thread.join();

        calc_logger::instance().info("Server stopped.");
        return 0;
    }

    catch (const std::exception& e)
    {
        calc_logger::instance().error(e.what());

        return 1;
    }
    
}