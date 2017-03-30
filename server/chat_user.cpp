//
// Created by demiaowu on 2017/3/29.
//
#include "chat_user.h"

namespace chat {
    namespace server {
        chat_user::chat_user(const uint64_t user_id)
                : user_id_(user_id) {
            std::string nick_name = chat_nickname_factory::get_nick_name(user_id);
            ::memcpy(nick_name_, nick_name.c_str(), nick_name.size());
        }
        chat_user::chat_user(const uint64_t user_id, const std::string& nick_name)
                : user_id_(user_id) {
            const int nick_name_len = nick_name.size();
            ::memcpy(nick_name_,
                     nick_name.c_str(),
                     nick_name_len > max_nick_name_len ? max_nick_name_len:nick_name_len);
        }

        uint64_t chat_user::get_user_id(){
            return user_id_;
        }

        const char* chat_user::get_nick_name() {
            return nick_name_;
        }

        void chat_user::set_nick_name(const std::string& nick_name) {
            const int nick_name_len = nick_name.size();
            ::memcpy(nick_name_,
                     nick_name.c_str(),
                     nick_name_len > max_nick_name_len ? max_nick_name_len:nick_name_len);
        }

        const std::string chat_user::to_msg() {
            _user_id_str user_id_str;
            user_id_str.user_id_ = user_id_;
            // |  id  |  nickname_ |
            char user_str[8 + max_nick_name_len];
            //size_t len = ;
            memcpy(user_str, user_id_str.str_, 8);
            memcpy(user_str+8, nick_name_, ::strlen(nick_name_));
            return std::string(user_str);
        }

        const std::string chat_user::to_string() {
            return std::string(nick_name_, strlen(nick_name_));
        }


    } // server namespace
} // chat namespace
