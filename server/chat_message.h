//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_MESSAGE_H
#define TCHAT_CHAT_MESSAGE_H

#include <cstring>
#include <cstdlib>
#include <deque>

#include "chat_config.h"
#include "logger.h"

namespace chat {
    namespace server {

        class chat_message {
        public:
            chat_message()
                : body_len_(0){

            }

            char* get_msg() {
                return msg_;
            }

            const char* get_command() const {
                return command_;
            }

            size_t get_msg_len() const {
                return MSG_HEADER_LEN + body_len_;
            }

            const char* get_command() {
                return command_;
            }

            size_t get_body_len() const {
                return body_len_;
            }

            char* get_body() {
                return msg_ + MSG_HEADER_LEN;
            }

            size_t get_header_len() {
                return MSG_HEADER_LEN;
            }

            void set_body_len(size_t len) {
                if (len >= chat::server::MAX_MSG_BODY_LEN) {
                    body_len_ = chat::server::MAX_MSG_BODY_LEN;
                    LOG_WARN << "chat message too long, the len is: " << len;
                } else {
                    body_len_ = len;
                }
            }

            bool decode_header() {
                char header[5] = "";
                memcpy(header, msg_, 4);
                LOG_TRACE << "+" <<(int)header[0] << ":" << (int)header[1] << ":"<< header[2] << ":" << header[3] << "+";
                body_len_ = (size_t)(header[0]) + 256*((size_t)(header[1]));
                LOG_TRACE << "body_len_ =" << body_len_;

                if (body_len_ > MAX_MSG_BODY_LEN) {
                    body_len_ = 0;
                    return false;
                }

                command_[0] = msg_[2];
                command_[1] = msg_[3];

                return true;
            }

            bool encode_header() {
                _header_str header_str;
                header_str.len_ = body_len_;
                memcpy(msg_, header_str.str_, 2);
            }

            bool encode(const char* body, const char *cmd, size_t body_len) {
                LOG_TRACE << body << "-" << cmd << "-" << body_len;
                _header_str header_str;
                header_str.len_ = body_len;
                memcpy(msg_, header_str.str_, 2);
                body_len_ = body_len;

                msg_[2] = cmd[0];
                msg_[3] = cmd[1];

                command_[0] = cmd[0];
                command_[1] = cmd[1];

                memcpy(msg_ + 4, body, body_len);
                LOG_TRACE << "send message :" << get_body();
            }

            std::string to_string() {
                return std::string(get_body());
            }

        private:
            // |    2     |    2     |   8   |   32   |   8   |   32   |  msg_content  |
            // |        header       |                        body                     |
            // |        header       |      from      |      to        |  msg_content  |
            // | body_len | command  |   id  |   name |   id  |   name |  msg_content  |
            char msg_[MSG_HEADER_LEN + MAX_MSG_BODY_LEN] = {0};
            char command_[2] = {0};
            size_t body_len_;

            union _header_str {
                unsigned short int len_;
                char str_[2];
            };
        }; // chat_message class

       typedef std::deque<chat_message> chat_message_queue;
    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_MESSAGE_H
