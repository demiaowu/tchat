set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        chat_client.cpp chat_client.h)


add_executable(client
        ${SOURCE_FILES})
target_link_libraries(client
        common_static
        server_static

        boost_system

        pthread)


add_library(client_static ${SOURCE_FILES})