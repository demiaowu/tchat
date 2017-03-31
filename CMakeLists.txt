cmake_minimum_required(VERSION 3.6)
project(tchat)

set(CMAKE_CXX_STANDARD 14)

set(GOOGLETEST_DIR F:/Libs/cygwin/googletest)


include_directories(
        ${PROJECT_SOURCE_DIR}/server
        ${PROJECT_SOURCE_DIR}/client
        ${PROJECT_SOURCE_DIR}/common
        ${PROJECT_SOURCE_DIR}/tests

        C:/cygwin64/usr/include
        ${GOOGLETEST_DIR}/include
        F:/Libs/cygwin/rapidjson/include)

link_directories(
        C:/cygwin64/lib
        ${GOOGLETEST_DIR}/libs)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/libs)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -fno-access-control")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")


add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(common)
add_subdirectory(tests)