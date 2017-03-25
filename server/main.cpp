//
// Created by demiaowu on 2017/3/24.
//
#include <iostream>

#include "chat_server.h"


int main(int argc, char* argv[]) {
    try
    {
        // Check command line arguments.
        if (argc != 3)
        {
            std::cerr << "Usage: http_server <address> <port> <doc_root>\n";
            std::cerr << "  For IPv4, try:\n";
            std::cerr << "    receiver 0.0.0.0 80 .\n";
            std::cerr << "  For IPv6, try:\n";
            std::cerr << "    receiver 0::0 80 .\n";
            return 1;
        }

        // Initialise the server.
        chat::server::chat_server s(argv[1], argv[2]);

        // Run the server until stopped.
        s.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}
