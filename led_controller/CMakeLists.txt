cmake_minimum_required(VERSION 2.8)
include_directories(src test/mocks)

add_executable(led_controller
    src/main.c
    src/detector/event_detector.c
    src/detector/key_input_detector.c
    src/detector/timeout_detector.c
    src/drivers/led_driver.c
    src/utils/logger.c
    src/os/io.c
    src/os/time.c)

add_executable(unittests
    src/detector/event_detector.c
    src/detector/key_input_detector.c
    src/detector/timeout_detector.c
    src/drivers/led_driver.c
    src/operator/operator.c
    src/operator/led_operator_factory.c
    test/key_input_event_test.cpp
    test/timer_event_test.cpp
    test/led_driver_test.cpp
    test/led_operator_test.cpp
    test/command_test.cpp
    test/mocks/os/mock_io.cpp
    test/mocks/utils/logger_spy.c)

target_link_libraries(led_controller ${LIBEVDEV_LIBRARIES})
target_link_libraries(unittests gmock_main)
