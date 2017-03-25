//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAT_MESSAGE_TEST_H
#define TCHAT_CHAT_MESSAGE_TEST_H

#include <gtest/gtest.h>
#include "chat_message.h"

using namespace chat::server;

TEST(chat_message_test, usage) {
    chat_message msg;
    EXPECT_EQ(0, msg.get_body_len());

    union _msg_header {
        unsigned short int len_;
        char header_[4];
    };

    _msg_header header;
    header.len_ = 88;
    header.header_[2] = 'a';
    header.header_[3] = 'b';
    memcpy(msg.get_msg(), header.header_, 4);

    msg.decode_header();
    EXPECT_EQ(88, msg.get_body_len());
    EXPECT_STREQ("ab", msg.get_command());

}

#endif //TCHAT_CHAT_MESSAGE_TEST_H
