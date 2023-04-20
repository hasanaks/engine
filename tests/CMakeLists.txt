add_executable(engine-test test.cpp motion.cpp collision.cpp)
target_link_libraries(engine-test doctest engine)
doctest_discover_tests(engine-test)
