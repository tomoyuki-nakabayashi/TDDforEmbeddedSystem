cmake_minimum_required(VERSION 2.8)
add_executable(evdev_test test/evdev_sample_test.cpp)
target_link_libraries(evdev_test gtest_main, ${LIBEVDEV_LIBRARIES})
