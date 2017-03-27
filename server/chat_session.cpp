//
// Created by demiaowu on 2017/3/25.
//
#include <boost/bind.hpp>

#include "chat_session.h"



namespace chat {
    namespace server {

        void chat_session::deliver_msg(const chat_message& msg) {
            connection_->deliver_msg(msg);
        }

        void chat_session::start() {
            room_manager_.get_connection_manager().start(connection_);
        }


    } // server namespace
} // chat namespace