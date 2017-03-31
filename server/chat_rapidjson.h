//
// Created by root on 17-3-30.
//

#ifndef TCHAT_CHAT_RAPIDJSON_H
#define TCHAT_CHAT_RAPIDJSON_H
#include <string>
#include <list>

#include "chat_room.h"
#include "chat_room_demo.h"


namespace chat {
    namespace server {



        std::string rooms_to_string(std::set<chat_room_ptr>& rooms);

        std::string rooms_to_string(std::list<chat_room_demo>& rooms);

        std::list<chat_room_demo> string_to_rooms(const std::string& json);

    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_RAPIDJSON_H
