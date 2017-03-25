#include <iostream>

#include <logger.h>

using namespace chat::common;

int main() {

    std::cout << logger::get_log_level() << " " << logger::get_log_level_name() << std::endl;

    return 0;
}