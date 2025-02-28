cmake_minimum_required(VERSION 3.14)
project(logger LANGUAGES CXX)

option(LOGGER_BUILD_TESTS "Build the tests" ON)

add_library(logger INTERFACE)
target_include_directories(logger INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(logger INTERFACE cxx_std_17)

# Add the tests
if(LOGGER_BUILD_TESTS)
    add_subdirectory(test)
else()
    message(STATUS "Logger is a header-only library. Include it in your project using #include \"logger.hpp\".")
endif()
