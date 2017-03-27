set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
       logger.cpp logger.h noncopyable.h)

#static library
add_library(common_static ${SOURCE_FILES})
#target_link_libraries()
