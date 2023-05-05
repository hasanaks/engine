set(DOCTEST_NO_INSTALL ON CACHE BOOL "Skip the installation process")

FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest
  GIT_TAG v2.4.9
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(doctest)
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
target_include_directories(doctest INTERFACE "${doctest_SOURCE_DIR}/doctest")
