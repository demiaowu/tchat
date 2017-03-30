//
// Created by demiaowu on 2017/3/24.
//
#include <gtest/gtest.h>

#include "logger_test.h"
#include "chat_user_test.h"
#include "chat_message_test.h"
#include "cpp_test.h"
#include "asio_test.h"
#include "boost_test.h"


int main(int argc, char* argv[]) {
    logger::set_log_level(logger::TRACE);

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}