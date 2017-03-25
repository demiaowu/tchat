//
// Created by demiaowu on 2017/3/25.
//

#include <algorithm>
#include "chat_room.h"

namespace chat {
    namespace server {

        void chat_room::join(chat_participant_ptr participant) {
            participants_.insert(participant);
        }

        void chat_room::leave(chat_participant_ptr participant) {
            participants_.erase(participant);
        }

        void chat_room::deliver_msg(const chat_message &msg) {
            std::for_each(participants_.begin(), participants_.end(),
            std::bind(&chat_participant::deliver_msg, std::placeholders::_1, msg));
        }

    } // server namespace
} // chat namespace