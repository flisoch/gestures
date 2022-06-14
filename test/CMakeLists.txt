project(unittest)

find_package(GTest CONFIG REQUIRED)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

################################
# Unit Tests
################################
# Add test cpp file
add_executable( unittest testgtest.cpp )
# Link test executable against gtest & gtest_main
target_link_libraries(unittest gtest gtest_main)
add_test( unittest unittest )