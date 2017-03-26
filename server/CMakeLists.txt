set(SOURCE_FILES
        main.cpp
        chat_message.h
        chat_user.h
        chat_config.h
        chat_session.h chat_session.cpp
        chat_participant.h
        chat_room.h chat_room.cpp
        chat_server.h chat_server.cpp chat_connection.h chat_connection.cpp chat_nickname_factory.h)




add_executable(server
        ${SOURCE_FILES})
target_link_libraries(server
        common_static   #common lib

        boost_system
        boost_thread
        pthread

        # wsock32 & ws2_32 should be add when build in windows for mingw
        # wsock32
        # ws2_32
        )
