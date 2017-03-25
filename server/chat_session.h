//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_SESSION_H
#define TCHAT_CHAT_SESSION_H

#include <boost/asio.hpp>

#include "chat_participant.h"
#include "chat_room.h"

namespace chat {
    namespace server {
        using namespace boost::asio;

        class chat_session
            : public chat_participant,
            public std::enable_shared_from_this<chat_session> {
        public:
            chat_session(io_service& io, chat_room& room)
                    : socket_(io),
                      room_(room) {

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
            chat_room& room_;
            chat_message read_msg_;
            enum { max_message_queue = 64 };
            chat_message_queue write_msgs_;
        }; // chat_message class

        using chat_session_ptr = std::shared_ptr<chat_session>;

    } // server namespace
} // chat namespace


#endif //TCHAT_CHAT_SESSION_H
