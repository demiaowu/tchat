
set(SOURCE_FILES
        main.cpp
        logger_test.h
        test_utils.h
        chat_user_test.h
        chat_message_test.h)


add_executable(tests
        ${SOURCE_FILES})
target_link_libraries(tests
        common_static

        gtest
        pthread)
