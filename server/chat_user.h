//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_USER_H
#define TCHAT_CHAT_USER_H

#include <string>

#include <cstdint>
#include <cstring>
#include <cstdio>

#include "chat_config.h"

namespace chat {
    namespace server {

        class chat_user {
        public:
            chat_user(const uint64_t user_id)
                    : user_id_(user_id) {
                // Default nick_name: nick-id
                ::memcpy(nick_name_, "nick-", 5);
                ::snprintf(nick_name_+5, MAX_NICK_NAME_LEN-5, "%llu", user_id);
            }
            chat_user(const uint64_t user_id, const std::string& nick_name)
                    : user_id_(user_id) {
                const int nick_name_len = nick_name.size();
                ::memcpy(nick_name_,
                         nick_name.c_str(),
                         nick_name_len > MAX_NICK_NAME_LEN ? MAX_NICK_NAME_LEN:nick_name_len);
                nick_name_[nick_name_len > MAX_NICK_NAME_LEN ? MAX_NICK_NAME_LEN:nick_name_len] = '\0';
            }

            uint64_t get_user_id_() const {
                return user_id_;
            }
            // The id cannot be change
            void set_user_id_(uint64_t user_id_) = delete;

            const char* get_nick_name_() const {
                return nick_name_;
            }

            void set_nick_name(const std::string& nick_name) {
                const int nick_name_len = nick_name.size();
                ::memcpy(nick_name_,
                         nick_name.c_str(),
                         nick_name_len > MAX_NICK_NAME_LEN ? MAX_NICK_NAME_LEN:nick_name_len);
                nick_name_[nick_name_len > MAX_NICK_NAME_LEN ? MAX_NICK_NAME_LEN:nick_name_len] = '\0';
            }

            std::string to_msg() {
                _user_id_str user_id_str;
                user_id_str.user_id_ = user_id_;
                // |  id  |  nickname_ |
                char user_str[8 + chat::server::MAX_NICK_NAME_LEN];
                //size_t len = ;
                memcpy(user_str, user_id_str.str_, 8);
                memcpy(user_str+8, nick_name_, ::strlen(nick_name_));
                return std::string(user_str);
            }

        private:
            uint64_t user_id_;
            char nick_name_[chat::server::MAX_NICK_NAME_LEN+1];    // The last char is '\0'

            union _user_id_str {
                uint64_t user_id_;
                char str_[8];
            };
        }; //chat_user class

    } // server namespace
} // chat namespace


#endif //TCHAT_CHAT_USER_H
