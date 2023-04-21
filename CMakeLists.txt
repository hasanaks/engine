cmake_minimum_required(VERSION 3.22)

project(engine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib
  GIT_TAG 4.2.0
  GIT_SHALLOW TRUE
)
FetchContent_Declare(
  raygui
  GIT_REPOSITORY https://github.com/raysan5/raygui
  GIT_TAG 3.2
  GIT_SHALLOW TRUE
)
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest
  GIT_TAG v2.4.9
  GIT_SHALLOW TRUE
)
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen
  GIT_TAG 3.4.0
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib doctest raygui)
FetchContent_Populate(eigen)

add_library(engine World.cpp Collision.cpp Constraint.cpp ImpulseSolver.cpp)
target_include_directories(engine PUBLIC ${eigen_SOURCE_DIR} ${raygui_SOURCE_DIR}/src)

add_executable(engine-exec main.cpp)
target_link_libraries(engine-exec engine raylib)

include_directories(${doctest_SOURCE_DIR}/doctest)
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)

include(CTest)
add_subdirectory(tests)
