//
// Created by demiaowu on 2017/3/29.
//

#ifndef TCHAT_CHAT_TIME_WHEEL_H
#define TCHAT_CHAT_TIME_WHEEL_H

#include <unordered_map>
#include <boost/circular_buffer.hpp>

namespace chat {
    namespace server {

        class chat_session;

        typedef struct _session_node {
            chat_session* session_;
            struct _session_node* pre_;
            struct _session_node* next_;
        } session_node;

        class session_list {
        public:
            void push_front(session_node* session);

            static void break_node(session_node* session);
        private:
            session_node* list_;
        };

        class chat_session_wheel {
        public:
            // 转动时间轮
            session_list* rotate();

            void update(uint64_t session_id);

            void add(chat_session* session);
        private:

            std::unordered_map<uint64_t , session_node*> locate_;
            boost::circular_buffer<session_list*> wheel_;
            size_t wheel_size_;
        };


    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_TIME_WHEEL_H
