FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen
  GIT_TAG 3.4.0
  GIT_SHALLOW TRUE
)
FetchContent_Populate(eigen)
add_library(eigen INTERFACE)
target_include_directories(eigen INTERFACE "${eigen_SOURCE_DIR}")
