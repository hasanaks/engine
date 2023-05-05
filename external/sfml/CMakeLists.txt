FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML
  GIT_TAG 2.5.1
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(sfml)

set(IMGUI_DIR ${IMGUI_SOURCE_DIR} CACHE STRING "imgui top-level directory" FORCE)
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "Use find_package to find SFML")
FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml
  GIT_TAG master
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(imgui-sfml)
