//
// Created by demiaowu on 2017/3/26.
//

#ifndef TCHAT_CHAT_CONNECTION_H
#define TCHAT_CHAT_CONNECTION_H
#include <deque>
#include <memory>

#include <boost/asio.hpp>

#include "chat_config.h"
#include "chat_message.h"
#include "chat_participant.h"
#include "chat_session.h"
#include "chat_room_manager.h"

using namespace boost::asio;

namespace chat {
    namespace server {

        class chat_connection
            : public chat_participant,
              public std::enable_shared_from_this<chat_connection> {
        public:
            chat_connection(chat::server::chat_room_manager& room_manager, io_service& io)
                    : room_manager_(room_manager),
                      socket_(io) {
            }

            void start();
            void stop();

            void handle_read_header(const boost::system::error_code& error);
            void handle_read_body(const boost::system::error_code& error);

            void deliver_msg(const chat_message& msg) override;
            void handle_write(const boost::system::error_code& error);

            boost::asio::ip::tcp::socket& get_socket() {
                return socket_;
            }

//            friend class chat_session;

        private:
            chat::server::chat_room_manager& room_manager_;
            ip::tcp::socket socket_;
            chat_message read_msg_;
            enum { max_message_queue_size =  chat::server::MAX_CONNECTION_MESSAGE_QUEUE_SIZE };
            chat_message_queue write_msgs_;
        }; // chat_message class

       typedef std::shared_ptr<chat_connection> chat_connection_ptr;

    } // server namespace
} // chat namespace


#endif //TCHAT_CHAT_CONNECTION_H
