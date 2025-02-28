cmake_minimum_required(VERSION 3.14)

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

target_include_directories(logger INTERFACE ${CMAKE_SOURCE_DIR})

add_executable(test_logger_message test_logger_message.cpp)
target_link_libraries(test_logger_message PRIVATE logger gtest_main)

add_executable(test_logger_stream test_logger_stream.cpp)
target_link_libraries(test_logger_stream PRIVATE logger gtest_main)

add_executable(test_logger_mutex test_logger_mutex.cpp)
target_link_libraries(test_logger_mutex PRIVATE logger gtest_main)

enable_testing()

add_test(NAME test_logger_message COMMAND test_logger_message)
add_test(NAME test_logger_stream COMMAND test_logger_stream)
add_test(NAME test_logger_mutex COMMAND test_logger_mutex)
