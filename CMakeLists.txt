cmake_minimum_required(VERSION 3.16)
project(gestures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(TARGET_SRC
    src/main.cpp
    src/EventHandler.cpp
    src/Finger.cpp
    src/Gesture.cpp
    src/GestureEmitter.cpp
)
FIND_PACKAGE(libconfig++ REQUIRED)

add_executable(gestures ${TARGET_SRC})
target_link_libraries(gestures config++)

set_property(TARGET gestures PROPERTY CXX_STANDARD 17)

