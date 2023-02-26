cmake_minimum_required(VERSION 3.22)

project(engine)

include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 4.2.0
  GIT_SHALLOW TRUE
)
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest
  GIT_TAG v2.4.9
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib doctest)

add_library(engine Vector.cpp World.cpp)
target_link_libraries(engine)

add_executable(engine-exec main.cpp)
target_link_libraries(engine-exec engine raylib)

include_directories(${doctest_SOURCE_DIR}/doctest)
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)

include(CTest)
add_subdirectory(tests)
