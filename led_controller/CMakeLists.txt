cmake_minimum_required(VERSION 2.8)
include_directories(src test/mocks)

set(common_src
    src/active_object_engine.c
    src/detector/event_detector.c
    src/detector/key_input_detector.c
    src/detector/timeout_detector.c
    src/drivers/led_driver.c
    src/command/command.c
    src/command/halt_engine.c
    src/command/count_total.c
    src/command/led_operator_factory.c
    src/command/action_on_trigger.c
    src/command/detect_chain.c
)

add_executable(led_controller
    src/main.c
    ${common_src}
    src/utils/logger.c
    src/os/io.c
    src/os/time.c)

    add_executable(three_times_in_two_sec
    src/three_times_in_two_sec.c
    ${common_src}
    src/utils/logger.c
    src/os/io.c
    src/os/time.c)

add_executable(unittests
    ${common_src}
    test/active_object_test.cpp
    test/key_input_event_test.cpp
    test/timer_event_test.cpp
    test/led_driver_test.cpp
    test/led_operator_test.cpp
    test/command_test.cpp
    test/mocks/os/mock_io.cpp
    test/mocks/utils/logger_spy.c)

target_link_libraries(led_controller ${LIBEVDEV_LIBRARIES} ${GLIB_LIBRARIES})
target_link_libraries(three_times_in_two_sec ${LIBEVDEV_LIBRARIES} ${GLIB_LIBRARIES})
target_link_libraries(unittests gmock_main ${GLIB_LIBRARIES})
