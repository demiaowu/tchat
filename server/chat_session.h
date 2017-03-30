//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_SESSION_H
#define TCHAT_CHAT_SESSION_H

#include <boost/asio.hpp>

#include "chat_participant.h"
#include "chat_connection.h"


namespace chat {
    namespace server {
        using namespace boost::asio;

        class chat_session_manager;
        class room_;

        class chat_session
            : public chat_participant {
        public:
            chat_session(chat_room& room, chat_session_manager& session_manager, io_service& io);

            void start();
            void stop();

            virtual void deliver_msg(const chat_message& msg);

            uint64_t get_session_id() const {
                return session_id_;
            }

            chat_connection_ptr get_connection() {
                return connection_;
            }

        private:
            chat_room& room_;
            chat_session_manager& session_manager_;
            chat_connection_ptr connection_;
            uint64_t  session_id_;
        }; // chat_message class

        typedef std::shared_ptr<chat_session> chat_session_ptr;

    } // server namespace
} // chat namespace


#endif //TCHAT_CHAT_SESSION_H
