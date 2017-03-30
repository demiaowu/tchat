//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_USER_H
#define TCHAT_CHAT_USER_H

#include <string>
#include <memory>

#include <cstdint>
#include <cstring>
#include <cstdio>

#include "chat_config.h"
#include "chat_nickname_factory.h"

namespace chat {
    namespace server {

        class chat_user {
        public:
            chat_user(const uint64_t user_id);
            chat_user(const uint64_t user_id, const std::string& nick_name);

            uint64_t get_user_id();
            // The id cannot be change
            void set_user_id_(uint64_t user_id_) = delete;

            const char* get_nick_name();
            void set_nick_name(const std::string& nick_name);

            const std::string to_msg();
            const std::string to_string();

        private:
            union _user_id_str {
                uint64_t user_id_;
                char str_[8];
            };
            enum {
                max_nick_name_len = chat::server::MAX_NICK_NAME_LEN
            };

        private:
            uint64_t user_id_;
            char nick_name_[max_nick_name_len] = {0};
        }; //chat_user class

        using chat_user_ptr = std::shared_ptr<chat_user>;

    } // server namespace
} // chat namespace


#endif //TCHAT_CHAT_USER_H
