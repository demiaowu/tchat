//
// Created by demiaowu on 2017/3/27.
//
#include "chat_room_manager.h"

namespace chat {
    namespace server {



        void chat_room_manager::start(chat_participant_ptr session) {
            sessions_.insert(session);
            (dynamic_cast<chat_session*>(session.get()))->start();
        }

        void chat_room_manager::deliver_msg(const chat_message& msg) {
        }

        void chat_room_manager::stop(chat_participant_ptr session) {

        }
        void chat_room_manager::stop_all() {

        }

        chat_connection_manager& chat_room_manager::get_connection_manager() {
            return connection_manager_;
        }

        void chat_room_manager::join(chat_participant_ptr participant) {
            sessions_.insert(participant);
        }
        void chat_room_manager::leave(chat_participant_ptr participant) {
            sessions_.erase(participant);
        }


    } // server namespace
} // chat namespace
