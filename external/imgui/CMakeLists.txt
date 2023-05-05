FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG v1.89.5
  GIT_SHALLOW TRUE
)
FetchContent_Populate(imgui)

add_compile_definitions(IMGUI_USER_CONFIG="${CMAKE_CURRENT_SOURCE_DIR}/imgui_config.h")
add_library(imgui ${imgui_SOURCE_DIR}/imgui.cpp
                  ${imgui_SOURCE_DIR}/imgui_demo.cpp
                  ${imgui_SOURCE_DIR}/imgui_draw.cpp
                  ${imgui_SOURCE_DIR}/imgui_tables.cpp
                  ${imgui_SOURCE_DIR}/imgui_widgets.cpp)
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR} ${eigen_SOURCE_DIR})
target_link_libraries(imgui eigen)
set(IMGUI_SOURCE_DIR ${imgui_SOURCE_DIR} PARENT_SCOPE)
