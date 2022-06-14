
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

set(TARGET_SRC 
    maintest.cpp
    TouchpadInputEventSourceTest.cpp
    )
add_executable( tests ${TARGET_SRC} )
target_link_libraries(tests PRIVATE
                        gtest 
                        gtest_main 
                        gestures
                        )
gtest_discover_tests(tests)