//
// Created by demiaowu on 2017/3/25.
//
#include <boost/bind.hpp>

#include "chat_session.h"
#include "chat_connection_manager.h"
#include "chat_room_manager.h"



namespace chat {
    namespace server {

        chat_session::chat_session(chat::server::chat_room_manager& room_manager, io_service& io)
            : room_manager_(room_manager) {
                connection_.reset(new chat_connection(room_manager_, io));
        }


        void chat_session::deliver_msg(const chat_message& msg) {
            connection_->deliver_msg(msg);
        }

        void chat_session::start() {
            room_manager_.get_connection_manager().start(connection_);
        }


    } // server namespace
} // chat namespace