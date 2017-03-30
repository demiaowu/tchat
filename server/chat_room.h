//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_ROOM_H
#define TCHAT_CHAT_ROOM_H

#include <map>
#include <memory>
#include <string>

#include "chat_config.h"
#include "chat_participant.h"
#include "chat_message.h"
#include "chat_session.h"

#include "chat_session_manager.h"
#include "chat_user.h"

namespace chat {
    namespace server {

        class chat_connection_manager;

        class chat_room {
        public:
            chat_room(chat_connection_manager& connection_manager);
            chat_room(uint64_t room_id, const std::string& room_name, chat_connection_manager& connection_manager);

            void start(chat_session_ptr session);
            void stop(chat_session_ptr session);

            void deliver_msg(const chat_message& msg);

            chat_session_manager& get_session_manager() {
                return session_manager_;
            }

            void join(boost::asio::ip::tcp::socket& socket);

        private:
            enum {
                max_room_name_len = chat::server::MAX_ROOM_NAME_LEN
            };

        private:
            chat_session_manager session_manager_;
            std::map<uint64_t, chat_user_ptr> users_;
            char room_name_[max_room_name_len] = {0};
            uint64_t room_id_;
        }; //chat_room class

        using chat_room_ptr = std::shared_ptr<chat_room>;
    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_ROOM_H
