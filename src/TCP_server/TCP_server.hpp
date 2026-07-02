#pragma once
#include <boost/asio.hpp>
#include <functional>
#include <memory>
#include <iostream>

using boost::asio::ip::tcp;

class TCP_Server
{
   private:
    boost::asio::io_context io_context_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    std::function<std::string(const std::string&)> data_handler_;

    void start_accept();
    void read_data();

   public:
    TCP_Server(std::function<std::string(const std::string&)> handler);
    void run();
    void stop();
};


