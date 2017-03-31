//
// Created by demiaowu on 2017/3/31.
//

#ifndef TCHAT_CHAT_ROOM_DEMO_H
#define TCHAT_CHAT_ROOM_DEMO_H
#include <string>

#include <cstdint>

#include "chat_config.h"

namespace chat {
    namespace server {


        class chat_room_demo {
        public:
            chat_room_demo() = default;
            chat_room_demo(const uint64_t room_id, const std::string& room_name)
                : room_id_(room_id){
                ::memcpy(room_name_, room_name.c_str(), room_name.size());
            }

            chat_room_demo(const chat_room_demo& room) {
                room_id_ = room.get_room_id();
                ::memcpy(room_name_, room.get_room_name(), strlen(room.get_room_name()));
            }

            chat_room_demo& operator= (const chat_room_demo& room) {
                if (this != &room) {
                    this->room_id_ = room.get_room_id();
                    ::memcpy(this->room_name_, room.get_room_name(), strlen(room.get_room_name()));
                }

                return *this;
            }


            uint64_t get_room_id() const{
                return room_id_;
            }

            void set_room_id(uint64_t room_id) {
                room_id_ = room_id;
            }

            const char* get_room_name() const {
                return room_name_;
            }

            void set_room_name(const std::string& room_name) {
                ::memcpy(this->room_name_, room_name.c_str(), room_name.size());
            }



        private:
            enum {
                max_room_name_len = chat::server::MAX_ROOM_NAME_LEN
            };

        private:

            char room_name_[max_room_name_len] = {0};
            uint64_t room_id_;
        }; //chat_room class

    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_ROOM_DEMO_H
