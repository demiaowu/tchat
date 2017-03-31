//
// Created by demiaowu on 17-3-30.
//
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>


#include "chat_rapidjson.h"
#include "chat_user.h"

namespace chat {
    namespace server {

        std::string rooms_to_string(std::set<chat_room_ptr>& rooms) {
            char json[] = "{\"rooms\":[]}";

            rapidjson::Document document;
            document.Parse(json);
            rapidjson::Value& json_rooms = document["rooms"];

            for (auto iter = rooms.begin(); iter != rooms.end(); ++ iter) {
                rapidjson::Value item(rapidjson::Type::kObjectType);
                item.AddMember(rapidjson::StringRef("id"), iter->get()->get_room_id(), document.GetAllocator());
                item.AddMember(rapidjson::StringRef("name"), rapidjson::StringRef(iter->get()->get_room_name()), document.GetAllocator());
                json_rooms.PushBack(item, document.GetAllocator());
            }

            // to string
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            document.Accept(writer);

            return buffer.GetString();
        }

        std::string rooms_to_string(std::list<chat_room_demo>& rooms) {
            char json[] = "{\"rooms\":[]}";

            rapidjson::Document document;
            document.Parse(json);
            rapidjson::Value& json_rooms = document["rooms"];

            for (auto iter = rooms.begin(); iter != rooms.end(); ++ iter) {
                rapidjson::Value item(rapidjson::Type::kObjectType);
                item.AddMember(rapidjson::StringRef("id"), iter->get_room_id(), document.GetAllocator());
                item.AddMember(rapidjson::StringRef("name"), rapidjson::StringRef(iter->get_room_name()), document.GetAllocator());
                json_rooms.PushBack(item, document.GetAllocator());
            }

            // to string
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            document.Accept(writer);

            return buffer.GetString();
        }

        std::list<chat_room_demo> string_to_rooms(const std::string& json) {
            rapidjson::Document document;
            document.Parse(json.c_str());
            rapidjson::Value& json_rooms = document["rooms"];

            std::list<chat_room_demo> rooms;

            for (size_t i = 0; i < json_rooms.Size(); i++) {
                rapidjson::Value& v = json_rooms[i];
                chat_room_demo room;
                if (v.HasMember("id") && v.HasMember("name")) {
                    chat_room_demo room(v["id"].GetUint64(), v["name"].GetString());
                    rooms.push_back(room);
                }
            }

            return rooms;
        }

    } // server namespace
} // chat namespace