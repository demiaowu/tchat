#include <iostream>

#include <boost/asio.hpp>

void deadtime_handler(const boost::system::error_code& ec) {
    std::cout << "deadtime handler" << std::endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    boost::asio::io_service io;
    boost::asio::deadline_timer timer(io, boost::posix_time::seconds(1));

    timer.async_wait(&deadtime_handler);

    io.run();

    return 0;
}
