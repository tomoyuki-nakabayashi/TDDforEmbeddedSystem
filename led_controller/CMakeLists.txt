cmake_minimum_required(VERSION 2.8)
include_directories(src test/mocks)

add_executable(led_controller
    src/main.c
    src/event_detector.c
    src/key_input_event.c
    src/timeout_detector.c
    src/led_driver.c
    src/utils/logger.c
    src/os/io.c)

add_executable(unittests
    src/key_input_event.c
    src/led_driver.c
    src/event_detector.c
    src/timeout_detector.c
    test/key_input_event_test.cpp
    test/timer_event_test.cpp
    test/led_driver_test.cpp
    test/command_test.cpp
    test/mocks/os/mock_io.cpp
    test/mocks/utils/logger_spy.c)

target_link_libraries(led_controller ${LIBEVDEV_LIBRARIES})
target_link_libraries(unittests gmock_main)
