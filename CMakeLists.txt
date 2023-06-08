cmake_minimum_required(VERSION 3.22)

project(engine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

add_subdirectory(external/imgui)
add_subdirectory(external/sfml)
add_subdirectory(external/eigen)

add_library(engine PhysicsWorld.cpp Collision.cpp Constraint.cpp ImpulseSolver.cpp Math.cpp)
target_link_libraries(engine PUBLIC eigen)

add_executable(engine-exec main.cpp Camera.cpp)
target_link_libraries(engine-exec engine sfml-graphics imgui ImGui-SFML::ImGui-SFML)
