cmake_minimum_required(VERSION 3.15)

add_executable(utilsTests ./event_emitter.cpp)
target_link_libraries(
    utilsTests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(utilsTests)