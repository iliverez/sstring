cmake_minimum_required(VERSION 3.14)
project(sstring)

set(CMAKE_CXX_STANDARD 17)
set(CMAME_CXX_STANDARD_REQUIRED_ON)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY  https://github.com/google/googletest.git
  GIT_TAG main
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

