cmake_minimum_required(VERSION 3.14)
project(logger LANGUAGES CXX)

option(BUILD_TESTS "Build the tests" ON)
option(NO_THREAD_SUPPORT "Disable thread support" OFF)

add_library(logger INTERFACE)
target_include_directories(logger INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(logger INTERFACE cxx_std_17)

if (NO_THREAD_SUPPORT)
    target_compile_definitions(logger INTERFACE NO_THREAD_SUPPORT)
endif()

# Add the tests
if(BUILD_TESTS)
    add_subdirectory(test)
else()
    message(STATUS "------------------------------------------------
        Logger is a header-only library.
            Include it in your project using #include \"logger.hpp\".
------------------------------------------------")
endif()
