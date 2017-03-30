//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_SERVER_H
#define TCHAT_CHAT_SERVER_H
#include <memory>
#include <string>
#include <unordered_map>

#include "noncopyable.h"
#include "chat_connection_manager.h"
#include "chat_room.h"
#include "chat_session.h"
#include "chat_config.h"
#include "chat_socket.h"

namespace chat {
    namespace server {


        class chat_server
                : public chat::common::noncopyable{
        public:
            chat_server(const std::string& address, const std::string& port);

            void run();

        private:

            void start_accept();
            void handle_accept(const boost::system::error_code& ec);

            void handle_stop();

            void start(chat_socket_ptr socket);

            uint64_t get_new_room_id();
            void create_room(const std::string room_name, boost::asio::ip::tcp::socket& socket);

            friend class chat_socket;


            boost::asio::io_service io_service_;
            boost::asio::signal_set signals_;
            boost::asio::ip::tcp::acceptor acceptor_;
            chat_connection_manager conncetion_manager_;

            std::set<chat_room_ptr> rooms_;
            std::unordered_map<uint64_t, bool> room_ids;

            std::set<chat_socket_ptr> sockets_;
            chat_socket_ptr new_socket_;
        }; //chat_server class


    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_SERVER_H
