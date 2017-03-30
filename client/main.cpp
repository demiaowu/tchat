//
// Created by demiaowu on 2017/3/24.
//
#include <iostream>
#include <thread>
#include <cstring>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "logger.h"
#include "chat_client.h"
#include "chat_message.h"
#include "chat_config.h"

using namespace chat::common;
using namespace chat::server;
using namespace chat::client;

using namespace std;

bool decode_comand(char* line, size_t& body_pos, char *cmd) {
    int n = 0;
    int len = strlen(line);
    while (n < len && line[n] == ' ') {
        ++ n;
    }

    LOG_TRACE << line+n;
    if (strncmp(line+n, "chat", 4)) {
        LOG_TRACE << "not equal to chat";
        return false;
    }

    n += 4;

    while (n < len && line[n] == ' ') {
        ++ n;
    }

    LOG_TRACE << line[n] << line[n+1];
    if (line[n] == '-') {
        ++ n;
        switch (line[n ++ ]) {
            case 's':
                LOG_TRACE << "发送消息";
                break;
            case 'l':
                LOG_TRACE << "列举所有room";
                break;
            case 'j':
                LOG_TRACE << "加入某个room";
                break;
            case 'c':
                LOG_TRACE << "切换到某个room";
                break;
            case 'e':
                LOG_TRACE << "退出";
                break;
            default:
                return false;
        }
        cmd[0] = line[n-1];
    } else {
        return false;
    }

    while (n < len && line[n] == ' ') {
        ++ n;
    }
    body_pos = n;

    return true;
}

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
            size_t body_pos;
            char cmd[2] = {0};
            if (decode_comand(line, body_pos, cmd)) {
                LOG_TRACE << line << "-" << cmd << "-" << body_pos;
                chat_message msg;
                msg.encode(line+body_pos, cmd, strlen(line+body_pos));
                LOG_TRACE << msg.to_string();
                client.write(msg);
            } else {
                std::cerr << "Enter error." << std::endl;
                std::cerr << "Enter should be format as follows:" << std::endl;
                std::cerr << "chat -l/-j/-c/-e [msg body]" << std::endl;
            }
            memset(line, 0, chat::server::MAX_MSG_BODY_LEN + 1);
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