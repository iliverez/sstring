add_executable(tests_run sstring_test.cpp)

target_link_libraries(tests_run sstring gtest gtest_main)

add_test(
 NAME tests
 COMMAND tests_run
)

