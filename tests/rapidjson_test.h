//
// Created by demiaowu on 17-3-30.
//

#ifndef TCHAT_RAPIDJSON_TEST_H
#define TCHAT_RAPIDJSON_TEST_H

#include <gtest/gtest.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>


char json[] = "{\"rooms\":[ { \"id\":10001, \"name\":\"room1\" }]}";

TEST(rapidjsontest, usage) {
    // Read
    rapidjson::Document document;
    document.Parse(json);
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

#endif //TCHAT_RAPIDJSON_TEST_H
