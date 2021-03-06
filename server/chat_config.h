//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_CONFIG_H_H
#define TCHAT_CHAT_CONFIG_H_H

//
// Some constants have been defined in here
//
#include <cstring>

namespace chat {
    namespace server {

        //The max length of the user's nick name
        const size_t MAX_NICK_NAME_LEN = 32;
        const size_t MAX_ROOM_NAME_LEN = 32;

        const size_t MSG_HEADER_LEN    = 4;
        const size_t MAX_MSG_BODY_LEN  = 512 + 80;

        const size_t MAX_CONNECTION_MESSAGE_QUEUE_SIZE = 64;


        // The version of chat
        const int chat_version = 1;

    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_CONFIG_H_H
