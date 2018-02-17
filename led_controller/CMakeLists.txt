cmake_minimum_required(VERSION 2.8)
include_directories(src test/mocks)

add_executable(led_controller
    src/main.c
    src/key_input_event.c
    src/utils/logger.c
    src/os/io.c)

add_executable(unittests
    src/key_input_event.c
    test/key_input_event_test.cpp
    test/mocks/utils/logger_spy.c)

target_link_libraries(led_controller ${LIBEVDEV_LIBRARIES})
target_link_libraries(unittests gmock_main)
