#include "Runner.hpp"

int main(int argc, char* argv[])
{   try
    {
        Runner runner;
        runner.Run(argc, argv);
    }
    catch(const std::exception& e)
    {
        calc_logger::instance().error(e.what());
        return 1;
    }
    return 0;
}