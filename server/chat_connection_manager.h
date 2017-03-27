//
// Created by demiaowu on 2017/3/26.
//

#ifndef TCHAT_CHAT_CONNECTION_MANAGER_H
#define TCHAT_CHAT_CONNECTION_MANAGER_H
#include <set>

#include "noncopyable.h"
#include "chat_participant.h"
#include "chat_manager.h"

namespace chat {
    namespace server {

        class chat_message;

        class chat_connection_manager
                  : public chat_manager,
                    public chat::common::noncopyable{
        public:
            void start(chat_participant_ptr con);

            void stop(chat_participant_ptr con);

            void stop_all();

            void deliver_msg(const chat_message& msg);

        private:
            std::set<chat_participant_ptr> connections_;
        }; // chat_connection_manager

    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_CONNECTION_MANAGER_H
