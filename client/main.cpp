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

        chat::common::logger::set_log_level(chat::common::logger::TRACE);

        chat_client client(argv[1], argv[2]);

        std::thread t(boost::bind(&chat::client::chat_client::run, &client));

        char line[chat::server::MAX_MSG_BODY_LEN + 1];
        while (std::cin.getline(line, chat::server::MAX_MSG_BODY_LEN + 1))
        {
            using namespace std; // For strlen and memcpy.
            chat_message msg;
            msg.set_body_len(strlen(line));
            memcpy(msg.get_body(), line, msg.get_body_len());
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