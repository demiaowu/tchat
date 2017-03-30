//
// Created by demiaowu on 2017/3/24.
//
#ifndef TCHAT_LOGGER_TEST_H
#define TCHAT_LOGGER_TEST_H

#include <iostream>

#include <logger.h>
#include <test_utils.h>

using namespace chat::common;

TEST(logger_test, usage) {
    std::cout << logger::get_log_level() << " " << logger::get_log_level_name() << std::endl;

    LOG_TRACE << "trace";
    LOG_DEBUG << "debug";
    LOG_INFO << "ceshi";
    LOG_WARN << "warn";
    LOG_ERROR << "error";
    // LOG_FATAL << "fatal";

    logger::set_log_level(logger::TRACE);
    std::cout << logger::get_log_level() << " " << logger::get_log_level_name() << std::endl;
    LOG_TRACE << "trace";
    LOG_DEBUG << "debug";
    LOG_INFO << "ceshi";
    LOG_WARN << "warn";
    LOG_ERROR << "error";
    // LOG_FATAL << "fatal";
}


#endif //TCHAT_LOGGER_TEST_H
