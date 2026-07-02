#pragma once
#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::tcp;

class Test_client {
private:
    boost::asio::io_context io_context_;
    tcp::socket socket_;

public:
    Test_client();
    std::string send(const std::string& jsonstring);
};

