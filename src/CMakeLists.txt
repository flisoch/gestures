
set(TARGET_SRC
    EventHandler.cpp
    Finger.cpp
    Gesture.cpp
    GestureEmitter.cpp
    TouchpadInputEventSource.cpp
)
add_library(gestures-lib ${TARGET_SRC})

FIND_PACKAGE(libconfig++ REQUIRED)
target_link_libraries(gestures-lib config++)
