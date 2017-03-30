//
// Created by demiaowu on 2017/3/25.
//
#include <memory>

#include "chat_room.h"

namespace chat {
    namespace server {

        chat_room::chat_room(chat_connection_manager& connection_manager)
            : session_manager_(this, connection_manager) {

        }

        chat_room::chat_room(uint64_t room_id, const std::string& room_name, chat_connection_manager& connection_manager)
            : session_manager_(this, connection_manager),
              room_id_(room_id){
            memcpy(room_name_, room_name.c_str(), room_name.size());

        }

        void chat_room::deliver_msg(const chat_message &msg) {
//            for(auto iter=participants_.begin(), )
        }

        void chat_room::start(chat_session_ptr session) {
            users_[session->get_session_id()] = std::make_shared<chat_user>(session->get_session_id());
            session_manager_.start(session);
        }

        void chat_room::stop(chat_session_ptr session) {

        }

        void chat_room::join(boost::asio::ip::tcp::socket &socket) {

        }


    } // server namespace
} // chat namespace