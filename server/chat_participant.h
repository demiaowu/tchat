//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_PARTICIPANT_H
#define TCHAT_CHAT_PARTICIPANT_H

#include <memory>
#include "chat_message.h"

namespace chat {
    namespace server {

        class chat_participant {
        public:
            chat_participant() = default;
            virtual ~chat_participant() = default;

            virtual void deliver_msg(const chat_message& msg) = 0;
        };

        using chat_participant_ptr = std::shared_ptr<chat_participant>;

    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_PARTICIPANT_H
