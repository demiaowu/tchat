//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_ROOM_H
#define TCHAT_CHAT_ROOM_H

#include <set>

#include "chat_participant.h"

namespace chat {
    namespace server {

        class chat_room {
        public:
            void join(chat_participant_ptr participant);
            void leave(chat_participant_ptr participant);

            void deliver_msg(const chat_message& msg);

        private:
            std::set<chat_participant_ptr> participants_;
            enum { max_recent_msgs = 64 };
            chat_message_queue recent_msgs_;
        }; //chat_room class


    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_ROOM_H
