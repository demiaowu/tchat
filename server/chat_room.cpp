//
// Created by demiaowu on 2017/3/25.
//
#include "chat_room.h"
#include "chat_room_manager.h"

namespace chat {
    namespace server {

        chat_room::chat_room(chat_room_manager& room_manager)
            : room_manager_(room_manager) {

        }

        void chat_room::join(chat_participant_ptr participant) {
            room_manager_.join(participant);
        }

        void chat_room::leave(chat_participant_ptr participant) {
            room_manager_.leave(participant);
        }

        void chat_room::deliver_msg(const chat_message &msg) {
//            for(auto iter=participants_.begin(), )
        }

    } // server namespace
} // chat namespace