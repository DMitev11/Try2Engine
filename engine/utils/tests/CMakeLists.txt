cmake_minimum_required(VERSION 3.26)
enable_testing()

add_executable(utilsTests event_emitter.cc ${ENGINE_ROOT})
target_link_libraries(
    utilsTests
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(utilsTests)