//
// Created by demiaowu on 17-3-30.
//

#ifndef TCHAT_RAPIDJSON_TEST_H
#define TCHAT_RAPIDJSON_TEST_H

#include <gtest/gtest.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include "chat_rapidjson.h"

using namespace chat::server;

std::string json("{\"rooms\":[ { \"id\":10001, \"name\":\"room1\" }]}");

TEST(rapidjsontest, usage) {
    // Read
    rapidjson::Document document;
    document.Parse(json.c_str());
    rapidjson::Value& rooms = document["rooms"];
    {
        for (size_t i=0; i < rooms.Size(); i++) {
            rapidjson::Value& v = rooms[i];
            if (v.HasMember("id")) {
                std::cout << v["id"].GetUint64() << ":";
            }
            if (v.HasMember("name")) {
                std::cout << v["name"].GetString() << std::endl;
            }
        }
    }


    EXPECT_EQ(1,1);

    //Write
    rapidjson::Value item(rapidjson::Type::kObjectType);
    item.AddMember("id", 10002, document.GetAllocator());
    item.AddMember("name", "room2", document.GetAllocator());
    rooms.PushBack(item, document.GetAllocator());
    {
        for (size_t i=0; i < rooms.Size(); i++) {
            rapidjson::Value& v = rooms[i];
            if (v.HasMember("id")) {
                std::cout << v["id"].GetUint64() << ":";
            }
            if (v.HasMember("name")) {
                std::cout << v["name"].GetString() << std::endl;
            }
        }
    }

    // to string
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    std::cout << buffer.GetString() << std::endl;
}


TEST(rapidjson_rooms, usage) {
    std::list<chat_room_demo> rooms = chat::server::string_to_rooms(json);
    EXPECT_EQ(1, rooms.size());

    std::list<chat_room_demo> room_list;
    room_list.push_back(chat::server::chat_room_demo(1002, "room2"));
    room_list.push_back(chat::server::chat_room_demo(1003, "room3"));
    room_list.push_back(chat::server::chat_room_demo(1004, "room4"));

    std::string json_rooms = chat::server::rooms_to_string(room_list);
    std::cout << json_rooms << std::endl;
    EXPECT_STREQ("{\"rooms\":[{\"id\":1002,\"name\":\"room2\"},{\"id\":1003,\"name\":\"room3\"},{\"id\":1004,\"name\":\"room4\"}]}", json_rooms.c_str());

}
#endif //TCHAT_RAPIDJSON_TEST_H
