cmake_minimum_required(VERSION 3.20)

project(SearchEngine
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(search_engine
    src/main.cpp
)

include(CTest)

if(BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
    )

    FetchContent_MakeAvailable(googletest)

    add_executable(search_engine_tests
        tests/SanityTest.cpp
    )

    target_link_libraries(search_engine_tests
        PRIVATE
            GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(search_engine_tests)
endif()
