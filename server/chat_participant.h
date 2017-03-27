//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_PARTICIPANT_H
#define TCHAT_CHAT_PARTICIPANT_H
#include <memory>


namespace chat {
    namespace server {

        class chat_message;

        class chat_participant {
        public:
            virtual void deliver_msg(const chat_message& msg) = 0;
        };

        typedef std::shared_ptr<chat_participant> chat_participant_ptr;

    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_PARTICIPANT_H
