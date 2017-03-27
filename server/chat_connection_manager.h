//
// Created by demiaowu on 2017/3/26.
//

#ifndef TCHAT_CHAT_CONNECTION_MANAGER_H
#define TCHAT_CHAT_CONNECTION_MANAGER_H
#include <set>

#include "noncopyable.h"
#include "chat_manager.h"
#include "chat_participant.h"

namespace chat {
    namespace server {

        class chat_connection_manager
//                : public chat_manager,
                  : public chat::common::noncopyable{
        public:
            void start(chat_participant_ptr con);

            void stop(chat_participant_ptr con);

            void stop_all();

        private:
            std::set<chat_participant_ptr> connections_;
        }; // chat_connection_manager

    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_CONNECTION_MANAGER_H
