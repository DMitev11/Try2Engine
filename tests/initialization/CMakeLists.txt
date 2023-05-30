add_executable(
    initialization_tests
    initialization.cc
    initialization2.cc
)
target_link_libraries(
    initialization_tests
    GTest::gtest_main
    initialization
)
target_link_directories(
    initialization_tests PUBLIC
    ${CMAKE_SOURCE_DIR}/engine
)
include(GoogleTest)
gtest_discover_tests(initialization_tests)