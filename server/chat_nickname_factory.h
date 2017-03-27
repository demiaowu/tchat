//
// Created by demiaowu on 2017/3/26.
//

#ifndef TCHAT_CHAT_NICKNAME_FACTORY_H
#define TCHAT_CHAT_NICKNAME_FACTORY_H

#include <string>

#include <cstring>
#include <cstdio>

#include "noncopyable.h"
#include "chat_config.h"

namespace chat {
    namespace server {

    // Since it's a anonymity chat room, a nick name will be random generation.
    class chat_nickname_factory
        : public chat::common::noncopyable {

    public:
        //TODO next version
        static const std::string get_nickname()  = delete;

        static const std::string get_nick_name(uint64_t user_id) {
            // Default nick_name: nick-id
            char nick_name[chat::server::MAX_NICK_NAME_LEN+1];
            ::memcpy(nick_name, "nick-", 5);
            ::snprintf(nick_name + 5, chat::server::MAX_NICK_NAME_LEN-5, "%lu", user_id);

            return std::string(nick_name);
        }

    private:

    }; //chat_nickname_factory class

    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_NICKNAME_FACTORY_H
