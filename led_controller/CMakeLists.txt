cmake_minimum_required(VERSION 2.8)
add_executable(unittests
    src/key_input_event.cpp
    test/key_input_event_test.cpp)
target_link_libraries(led_controller gtest_main)
