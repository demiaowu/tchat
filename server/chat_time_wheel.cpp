//
// Created by demiaowu on 2017/3/29.
//

#include "chat_time_wheel.h"

namespace chat {
    namespace server {


        session_list* chat_session_wheel::rotate() {
            session_list* front = wheel_.front();
            // push_back一个空的session_list

            return front;
        }

        void chat_session_wheel::update(uint64_t session_id) {
            session_node* session = locate_[session_id];
            session_list::break_node(session);
            wheel_[wheel_size_-1]->push_front(session);
        }

        void chat_session_wheel::add(chat_session *session) {

        }
    } // server namespace
} // chat namespace