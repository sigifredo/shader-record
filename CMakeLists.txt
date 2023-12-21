cmake_minimum_required(VERSION 3.16)
project(record VERSION 1.0.0 LANGUAGES CXX)

include("config/record.cmake")
include("config/deps.cmake")
include("config/install.cmake")

include_directories(include)

# set (MOC_CLIENT_TEST_HDRS
# include/OFApp.hpp
# )

set (CLIENT_TEST_SRCS
src/OFApp.cpp
src/ofxVideoRecorder.cpp
)

add_executable(record ${CLIENT_TEST_SRCS} src/main.cpp)

# message(${OF_LIBRARIES})

target_link_libraries(record PUBLIC ${GST_LIBRARIES} ${OF_LIBRARIES})
# target_link_libraries(record PUBLIC ${OF_LIBRARIES})
