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
add_executable(gestures ${TARGET_SRC})
set_property(TARGET gestures PROPERTY CXX_STANDARD 17)

