//
// Created by demiaowu on 2017/3/26.
//

#ifndef TCHAT_CHAT_CONNECTION_H
#define TCHAT_CHAT_CONNECTION_H
#include <deque>
#include <memory>

#include <boost/asio.hpp>

#include "chat_config.h"
#include "chat_participant.h"
#include "chat_message.h"




namespace chat {
    namespace server {

        using namespace boost::asio;

        class chat_room;
        class chat_session;

        class chat_connection
            : public chat_participant,
              public std::enable_shared_from_this<chat_connection> {
        public:
            chat_connection(chat_room& room, chat_session* session, io_service& io);

            void start();
            void stop();

            void handle_read_header(const boost::system::error_code& error);
            void handle_read_body(const boost::system::error_code& error);

            void deliver_msg(const chat_message& msg);
            void handle_write(const boost::system::error_code& error);

            chat_session* get_chat_session();

            std::shared_ptr<boost::asio::ip::tcp::socket> get_socket() {
                return socket_;
            }

//            friend class chat_session;
        friend class chat_server;

        private:
            chat_session* session_;
            chat_room& room_;
            // The boost::asio::ip::tcp::socket have no copy constrcutor, so the best choise is shared_ptr
            std::shared_ptr<boost::asio::ip::tcp::socket> socket_;
            chat_message read_msg_;

            enum { max_message_queue_size =  chat::server::MAX_CONNECTION_MESSAGE_QUEUE_SIZE };
            chat_message_queue write_msgs_;
        }; // chat_message class

       typedef std::shared_ptr<chat_connection> chat_connection_ptr;

    } // server namespace
} // chat namespace


#endif //TCHAT_CHAT_CONNECTION_H
