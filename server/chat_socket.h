//
// Created by demiaowu on 2017/3/29.
//

#ifndef TCHAT_CHAT_SOCKET_H
#define TCHAT_CHAT_SOCKET_H
#include <boost/asio.hpp>


#include "chat_config.h"
#include "chat_message.h"

namespace chat {
    namespace server {

        using namespace boost::asio;

        class chat_server;

        class chat_socket
            : public std::enable_shared_from_this<chat_socket>{
        public:
            chat_socket(chat_server& server, io_service& io);

            void start();
            void stop();

            void handle_read_header(const boost::system::error_code& error);
            void handle_read_body(const boost::system::error_code& error);

            void deliver_msg(const chat_message& msg);
            void handle_write(const boost::system::error_code& error);


            std::shared_ptr<boost::asio::ip::tcp::socket> get_socket() {
                return socket_;
            }

//            friend class chat_session;

        private:
            chat_server& server_;
            std::shared_ptr<boost::asio::ip::tcp::socket> socket_;
            chat_message read_msg_;

            enum { max_message_queue_size =  chat::server::MAX_CONNECTION_MESSAGE_QUEUE_SIZE };
            chat_message_queue write_msgs_;
        }; // chat_message class

        using chat_socket_ptr = std::shared_ptr<chat_socket>;

    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_SOCKET_H
