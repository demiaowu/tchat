//
// Created by demiaowu on 2017/3/27.
//
#include "chat_session_manager.h"
#include "chat_connection_manager.h"
#include "chat_session.h"
#include "chat_room.h"

namespace chat {
    namespace server {

        chat_session_manager::chat_session_manager(chat_room* room, chat_connection_manager& connection_manager)
            : room_(room),
              connection_manager_(connection_manager) {

        }

        void chat_session_manager::start(chat_participant_ptr session) {
            sessions_.insert(session);
            session->start();
        }

        void chat_session_manager::deliver_msg(const chat_message& msg) {
            for(auto iter = sessions_.begin(); iter != sessions_.end(); ++iter) {
                iter->get()->deliver_msg(msg);
            }
        }

        void chat_session_manager::stop(chat_participant_ptr session) {
            session->stop();
            sessions_.erase(session);
            LOG_TRACE << "erase session:";
        }
        void chat_session_manager::stop_all() {

        }

        chat_connection_manager& chat_session_manager::get_connection_manager() {
            return connection_manager_;
        }

        chat_room *chat_session_manager::get_room() {
            return room_;
        }


    } // server namespace
} // chat namespace
