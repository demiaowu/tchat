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

            const char* get_msg() const {
                return msg_;
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

            const char* get_body() const {
                return msg_ + MSG_HEADER_LEN;
            }

            size_t get_body_len() const {
                return body_len_;
            }

            char* get_body() {
                return msg_ + MSG_HEADER_LEN;
            }

            static size_t get_header_len() {
                return MSG_HEADER_LEN;
            }

            bool decode_header() {
                char header[3] = "";
                memcpy(header, msg_, 2);
                header[2] = '\0';
                LOG_TRACE << "header: " << header[0] << ":" << (int)(header[0]) << "-" << header[1];
                body_len_ = (size_t)(header[0]) + 256*((size_t)(header[1]));
                LOG_TRACE << "body_len_ =" << body_len_;

                if (body_len_ > MAX_MSG_BODY_LEN) {
                    body_len_ = 0;
                    return false;
                }

                memcpy(command_, msg_+2, 2);

                return true;
            }

        private:
            // |    2     |    2     |   8   |   32   |   8   |   32   |  msg_content  |
            // |        header       |                        body                     |
            // |        header       |      from      |      to        |  msg_content  |
            // | body_len | command  |   id  |   name |   id  |   name |  msg_content  |
            char msg_[MSG_HEADER_LEN + MAX_MSG_BODY_LEN];
            char command_[2];
            size_t body_len_;
        }; // chat_message class

        using chat_message_queue = std::deque<chat_message>;
    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_MESSAGE_H
