//
// Created by demiaowu on 2017/3/25.
//
#include <boost/bind.hpp>

#include "chat_session.h"
#include "chat_connection_manager.h"
#include "chat_session_manager.h"



namespace chat {
    namespace server {

        chat_session::chat_session(chat_room& room, chat_session_manager& session_manager, io_service& io)
            : room_(room),
              session_manager_(session_manager) {
                connection_.reset(new chat_connection(*session_manager.get_room(), this, io));
            session_id_ = connection_.get()->get_socket()->native();
        }


        void chat_session::deliver_msg(const chat_message& msg) {
            connection_->deliver_msg(msg);
        }

        void chat_session::start() {
            session_manager_.get_connection_manager().start(connection_);
        }

        void chat_session::stop() {
            session_manager_.get_connection_manager().stop(connection_);
        }


    } // server namespace
} // chat namespace