cmake_minimum_required(VERSION 3.16)
project(gestures)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

SET ( PATH_INCLUDE "${PROJECT_SOURCE_DIR}/include" )
include_directories(${PATH_INCLUDE})

add_subdirectory(src)
add_subdirectory(app)
enable_testing()
add_subdirectory(test)

set_property(TARGET gestures PROPERTY CXX_STANDARD 17)

