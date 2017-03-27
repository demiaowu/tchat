//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_CLIENT_H
#define TCHAT_CHAT_CLIENT_H
#include <string>

#include <boost/asio.hpp>

#include "chat_message.h"
#include "noncopyable.h"

namespace chat {
    namespace client {

        class chat_client
            : public chat::common::noncopyable{
        public:
            chat_client(const std::string& address, const std::string& port);

            void run();
            void close();
            void write(const chat::server::chat_message& msg);

        private:
            void do_write(const chat::server::chat_message& msg);
            void do_close();

            void handle_connect(const boost::system::error_code& ec);
            void handle_write(const boost::system::error_code& ec);
            void handle_read_header(const boost::system::error_code& ec);
            void handle_read_body(const boost::system::error_code &ec);
            void handle_stop();

            boost::asio::io_service io_service_;
            boost::asio::ip::tcp::socket socket_;
            boost::asio::signal_set signals_;
            chat::server::chat_message read_msg_;
            enum { max_message_queue_size = 64 };
            chat::server::chat_message_queue write_msgs_;
        }; //chat_client

    } // client namespace
} // chat namespace

#endif //TCHAT_CHAT_CLIENT_H
