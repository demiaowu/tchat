//
// Created by demiaowu on 2017/3/26.
//

#ifndef TCHAT_CHAT_CONNECTION_H
#define TCHAT_CHAT_CONNECTION_H
#include <deque>

#include <boost/asio.hpp>

#include "chat_config.h"
#include "chat_message.h"

namespace chat {
    namespace server {
        using namespace boost::asio;

        class chat_connection
            : public std::enable_shared_from_this<chat_connection> {
        public:
            chat_connection(io_service& io)
                    : socket_(io) {
            }

            void start();

            void handle_read_header(const boost::system::error_code& error);
            void handle_read_body(const boost::system::error_code& error);

            void deliver_msg(const chat_message& msg);
            void handle_write(const boost::system::error_code& error);

            boost::asio::ip::tcp::socket& get_socket() {
                return socket_;
            }

        private:
            ip::tcp::socket socket_;
            chat_message read_msg_;
            enum { max_message_queue_size =  chat::server::MAX_CONNECTION_MESSAGE_QUEUE_SIZE; };
            chat_message_queue write_msgs_;
        }; // chat_message class

        using chat_connection_ptr = std::shared_ptr<chat_connection>;

    } // server namespace
} // chat namespace


#endif //TCHAT_CHAT_CONNECTION_H
