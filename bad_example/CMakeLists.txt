cmake_minimum_required(VERSION 2.8)
add_executable(bad_example bad_example.c)
target_link_libraries(bad_example ${LIBEVDEV_LIBRARIES})
