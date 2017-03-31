set(SOURCE_FILES
        main.cpp
        chat_message.h
        chat_user.h
        chat_config.h
        chat_session.h chat_session.cpp
        chat_participant.h
        chat_room.h chat_room.cpp
        chat_server.h chat_server.cpp
        chat_connection.h chat_connection.cpp
        chat_nickname_factory.h
        chat_connection_manager.cpp chat_connection_manager.h
        chat_manager.h
        chat_session_manager.h chat_session_manager.cpp
        #chat_time_wheel.cpp chat_time_wheel.h
        chat_user.cpp
        chat_socket.cpp chat_socket.h
        #chat_timeout_manager.cpp chat_timeout_manager.h
        chat_room_demo.h
        chat_rapidjson.h chat_rapidjson.cpp)




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

add_library(server_static ${SOURCE_FILES})