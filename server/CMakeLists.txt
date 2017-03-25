set(SOURCE_FILES
        main.cpp)




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
