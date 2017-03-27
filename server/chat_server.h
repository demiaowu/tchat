//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_SERVER_H
#define TCHAT_CHAT_SERVER_H
#include "noncopyable.h"
#include "chat_manager.h"
#include "chat_connection_manager.h"
#include "chat_room_manager.h"
#include "chat_session.h"

namespace chat {
    namespace server {

        class chat_server
                : public chat::common::noncopyable{
        public:
            chat_server(const std::string& address, const std::string& port);

            void run();

        private:

            void handle_stop();

            void start_accept();

            void handle_accept(const boost::system::error_code& ec);

            boost::asio::io_service io_service_;
            boost::asio::signal_set signals_;
            boost::asio::ip::tcp::acceptor acceptor_;
            chat_connection_manager conncetion_manager_;
            chat_room_manager room_manager_;
            chat_session_ptr new_session_;
        }; //chat_server class


    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_SERVER_H
