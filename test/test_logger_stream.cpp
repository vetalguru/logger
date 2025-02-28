// Copyright (c) 2025 Vitalii Shkibtan. All rights reserved.

#include <gtest/gtest.h>

#include <vector>
#include <string>

#include "include/logger.hpp"

const char kExpectedMessage[] = "Test stream message";


TEST(TestLoggerStream, LogTraceStream) {
    const std::string expectedLevel = "TRACE";

    testing::internal::CaptureStdout();
    LOG_TRACE << kExpectedMessage;
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find(kExpectedMessage), std::string::npos);
    EXPECT_NE(output.find(expectedLevel), std::string::npos);
}

TEST(TestLoggerStream, LogDebugStream) {
    const std::string expectedLevel = "DEBUG";

    testing::internal::CaptureStdout();
    LOG_DEBUG << kExpectedMessage;
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find(kExpectedMessage), std::string::npos);
    EXPECT_NE(output.find(expectedLevel), std::string::npos);
}

TEST(TestLoggerStream, LogInfoStream) {
    const std::string expectedLevel = "INFO";

    testing::internal::CaptureStdout();
    LOG_INFO << kExpectedMessage;
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find(kExpectedMessage), std::string::npos);
    EXPECT_NE(output.find(expectedLevel), std::string::npos);
}

TEST(TestLoggerStream, LogWarningStream) {
    const std::string expectedLevel = "WARNING";

    testing::internal::CaptureStdout();
    LOG_WARNING << kExpectedMessage;
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find(kExpectedMessage), std::string::npos);
    EXPECT_NE(output.find(expectedLevel), std::string::npos);
}

TEST(TestLoggerStream, LogErrorStream) {
    const std::string expectedLevel = "ERROR";

    testing::internal::CaptureStderr();
    LOG_ERROR << kExpectedMessage;
    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_NE(output.find(kExpectedMessage), std::string::npos);
    EXPECT_NE(output.find(expectedLevel), std::string::npos);
}

TEST(TestLoggerStream, LogFatalStream) {
    const std::string expectedLevel = "FATAL";

    testing::internal::CaptureStderr();
    LOG_FATAL << kExpectedMessage;
    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_NE(output.find(kExpectedMessage), std::string::npos);
    EXPECT_NE(output.find(expectedLevel), std::string::npos);
}
