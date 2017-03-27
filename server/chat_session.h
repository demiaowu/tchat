//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_SESSION_H
#define TCHAT_CHAT_SESSION_H

#include <boost/asio.hpp>

#include "chat_participant.h"
#include "chat_connection.h"
#include "chat_room_manager.h"
#include "chat_room.h"



namespace chat {
    namespace server {
        using namespace boost::asio;

        class chat_session
            : public chat_participant {
        public:
            chat_session(chat::server::chat_room_manager& room_manager, io_service& io)
                    : room_manager_(room_manager) {
                connection_.reset(new chat_connection(room_manager_, io));
            }

            void start();

            virtual void deliver_msg(const chat_message& msg);


            chat_connection_ptr get_connection() {
                return connection_;
            }

        private:
            chat_room_manager& room_manager_;
            chat::server::chat_connection_ptr connection_;
        }; // chat_message class

        typedef std::shared_ptr<chat_session> chat_session_ptr;

    } // server namespace
} // chat namespace


#endif //TCHAT_CHAT_SESSION_H
