//
// Created by demiaowu on 2017/3/24.
//
#include <iostream>
#include <thread>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "logger.h"
#include "chat_client.h"
#include "chat_message.h"
#include "chat_config.h"

using namespace chat::common;
using namespace chat::server;
using namespace chat::client;

int main(int argc, char *argv[]) {

    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: chat_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query(argv[1], argv[2]);
        boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

        chat_client client(io_service, iterator);

        std::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

        char line[chat::server::MAX_MSG_BODY_LEN + 1];
        while (std::cin.getline(line, chat::server::MAX_MSG_BODY_LEN + 1))
        {
            using namespace std; // For strlen and memcpy.
            chat_message msg;
            msg.body_length(strlen(line));
            memcpy(msg.body(), line, msg.body_length());
            msg.encode_header();
            client.write(msg);
        }

        client.close();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}