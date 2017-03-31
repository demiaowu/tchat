//
// Created by root on 17-3-30.
//

#ifndef TCHAT_CHAT_RAPIDJSON_H
#define TCHAT_CHAT_RAPIDJSON_H
#include <string>

#include "chat_room.h"


namespace chat {
    namespace server {

        std::string& rooms_to_string(std::set<chat_room_ptr>& rooms);

        std::set<chat_room_ptr>& string_to_rooms(const std::string& str);

    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_RAPIDJSON_H
