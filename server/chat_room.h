//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_ROOM_H
#define TCHAT_CHAT_ROOM_H

#include <set>

#include "chat_participant.h"
#include "chat_message.h"

#include "chat_room_manager.h"

namespace chat {
    namespace server {

        class chat_room {
        public:
            chat_room(chat_room_manager& room_manager);

            void join(chat_participant_ptr participant);
            void leave(chat_participant_ptr participant);

            void deliver_msg(const chat_message& msg);

        private:
            chat_room_manager& room_manager_

        }; //chat_room class


    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_ROOM_H
