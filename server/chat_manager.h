//
// Created by demiaowu on 2017/3/26.
//

#ifndef TCHAT_CHAT_MANAGER_H_H
#define TCHAT_CHAT_MANAGER_H_H

#include "chat_participant.h"

namespace chat {
    namespace server {

        class chat_manager;

        using chat_manager_ptr = std::shared_ptr<chat_manager>;

        class chat_manager
                : public chat_participant{
        public:
            chat_manager() = default;
//            chat_manager(chat_manager_ptr chat_manager_ptr) {
//
//            }
            virtual void start(chat_participant_ptr) = 0;
            virtual void stop(chat_participant_ptr) = 0;
            virtual void stop_all() = 0;
        };



    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_MANAGER_H_H
