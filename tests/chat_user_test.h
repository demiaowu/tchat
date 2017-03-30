//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_CHAR_USER_TEST_H
#define TCHAT_CHAR_USER_TEST_H
#include <cstring>

#include <gtest/gtest.h>
#include <chat_user.h>

using namespace chat::server;

TEST(chat_user_test, usage) {
    chat_user user1(1);
    EXPECT_EQ(1, user1.get_user_id());
    EXPECT_STREQ("nick-1", user1.get_nick_name());
    EXPECT_EQ(::strlen("nick-1"), ::strlen(user1.get_nick_name()));

    chat_user user2(2, "demiaowu");
    EXPECT_EQ(2, user2.get_user_id());
    EXPECT_STREQ( "demiaowu", user2.get_nick_name());

    user2.set_nick_name(std::string("demiaowu123").c_str());
    EXPECT_STREQ("demiaowu123", user2.get_nick_name());

    chat_user user3(2, "12345678901234567890123456789012");
    EXPECT_STREQ("12345678901234567890123456789012", user3.to_string().c_str());
}

#endif //TCHAT_CHAR_USER_TEST_H
