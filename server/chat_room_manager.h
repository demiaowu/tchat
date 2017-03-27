//
// Created by demiaowu on 2017/3/26.
//

#ifndef TCHAT_CHAT_SESSION_MANAGER_H
#define TCHAT_CHAT_SESSION_MANAGER_H
#include <set>

#include "chat_manager.h"
#include "chat_participant.h"
#include "chat_room.h"
#include "chat_session.h"
#include "chat_connection_manager.h"
#include "noncopyable.h"

namespace chat {
    namespace server {

        class chat_room_manager
                : public chat::common::noncopyable{
        public:
            chat_room_manager(chat_connection_manager& connection_manager)
                    : connection_manager_(connection_manager) {

            }

            void start(chat_participant_ptr session);

            void deliver_msg(const chat_message& msg);

            void stop(chat_participant_ptr session);
            void stop_all();

            chat_connection_manager& get_connection_manager();

            void join(chat_participant_ptr participant);
            void leave(chat_participant_ptr participant);


        private:
            chat_connection_manager& connection_manager_;
            std::set<chat_participant_ptr> sessions_;
        };


    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_SESSION_MANAGER_H
