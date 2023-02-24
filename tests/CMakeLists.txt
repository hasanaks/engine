add_executable(motion motion.cpp)
target_link_libraries(motion doctest engine)
doctest_discover_tests(motion)
