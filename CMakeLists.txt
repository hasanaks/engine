cmake_minimum_required(VERSION 3.22)

set(OpenGL_GL_PREFERENCE "GLVND")

project(engine)
add_executable(engine main.cpp)

include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 4.2.0
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib)

target_link_libraries(engine raylib)
