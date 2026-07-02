#include "test_client.hpp"

Test_client::Test_client()
    : io_context_(), socket_(io_context_) {
    tcp::endpoint ep(boost::asio::ip::make_address("127.0.0.1"), 8080);
    socket_.connect(ep);
}

std::string Test_client::send(const std::string& jsonstring) {
    boost::asio::write(socket_, boost::asio::buffer(jsonstring + "\n"));

    boost::asio::streambuf buf;
    boost::asio::read_until(socket_, buf, '\n');
    std::istream stream(&buf);
    std::string response;
    std::getline(stream, response);
    return response;
}