
set(TARGET_SRC
    EventHandler.cpp
    Finger.cpp
    Gesture.cpp
    GestureEmitter.cpp
    TouchpadInputEventSource.cpp
)
add_library(gestures ${TARGET_SRC})

FIND_PACKAGE(libconfig++ REQUIRED)
target_link_libraries(gestures PRIVATE config++)
