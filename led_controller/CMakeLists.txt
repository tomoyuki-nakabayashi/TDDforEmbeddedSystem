cmake_minimum_required(VERSION 2.8)
include_directories(src)
add_executable(unittests
    src/key_input_event.c
    test/key_input_event_test.cpp)
target_link_libraries(unittests gtest_main)
