//
// Created by root on 17-3-30.
//

#include "chat_rapidjson.h"
#include "chat_user.h"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace chat {
    namespace server {

        std::string& rooms_to_string(std::set<chat_room_ptr>& rooms) {
            return;
        }

        std::set<chat_room_ptr>& string_to_rooms(const std::string& str) {
            return;
        }

    } // server namespace
} // chat namespace