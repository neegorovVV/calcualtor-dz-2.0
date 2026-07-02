#include "TCP_server.hpp"

TCP_Server::TCP_Server(std::function<std::string(const std::string&)> handler)
    : io_context_(),
      acceptor_(io_context_, tcp::endpoint(tcp::v4(), 8080)),
      socket_(io_context_),
      data_handler_(handler)
{
    start_accept();
}

void TCP_Server::run()
{
    io_context_.run();
}

void TCP_Server::start_accept() {
    acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
        if (!ec) {
            read_data();  
        } else {
            
            start_accept();
        }
    });
}

void TCP_Server::read_data() {
    auto buffer = std::make_shared<boost::asio::streambuf>();
    boost::asio::async_read_until(socket_, *buffer, "\n",
        [this, buffer](boost::system::error_code ec, size_t bytes) {
            if (!ec && data_handler_) {
                std::istream is(buffer.get());
                std::string data;
                std::getline(is, data);
                
                std::string response = data_handler_(data);
                boost::asio::write(socket_, boost::asio::buffer(response + "\n"));
            }
                        
            socket_.close();
            
            socket_ = tcp::socket(io_context_);
            start_accept();
        });
}
void TCP_Server::stop()
{
    io_context_.stop();
}