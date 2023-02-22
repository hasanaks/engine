add_executable(motion motion.cpp)
target_link_libraries(motion doctest raylib)
doctest_discover_tests(motion)
