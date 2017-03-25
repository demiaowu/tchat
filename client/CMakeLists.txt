set(SOURCE_FILES
        main.cpp)


add_executable(client
        ${SOURCE_FILES})
target_link_libraries(client
        common_static)