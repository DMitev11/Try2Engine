cmake_minimum_required(VERSION 3.26)

include(FetchContent)
FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/b796f7d44681514f58a683a3a71ff17c94edb0c1.zip # 1.13.x
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    enable_testing()
endif()

set(TESTS)

if(DEFINED WITH_SDL AND WITH_SDL)
    set(TESTS ${TESTS}
        sdl_renderer_object.cc
    )
endif()

message(STATUS "TESTS ${TESTS}")
add_executable(
    objects_tests
    ${TESTS}
)
target_link_libraries(
    objects_tests
    GTest::gtest_main
    objects
)
include(GoogleTest)
gtest_discover_tests(objects_tests)