// Copyright (c) 2025 Vitalii Shkibtan. All rights reserved.

#include <gtest/gtest.h>

#include <vector>
#include <string>

#include "include/logger.hpp"

const char kExpectedMessage[] = "Test message";


TEST(TestLoggerMessage, LogTraceMessage) {
    const std::string expectedLevel = "TRACE";

    testing::internal::CaptureStdout();
    LOG_TRACE_MSG(kExpectedMessage);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find(kExpectedMessage), std::string::npos);
    EXPECT_NE(output.find(expectedLevel), std::string::npos);
}

TEST(TestLoggerMessage, LogDebugMessage) {
    const std::string expectedLevel = "DEBUG";

    testing::internal::CaptureStdout();
    LOG_DEBUG_MSG(kExpectedMessage);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find(kExpectedMessage), std::string::npos);
    EXPECT_NE(output.find(expectedLevel), std::string::npos);
}

TEST(TestLoggerMessage, LogInfoMessage) {
    const std::string expectedLevel = "INFO";

    testing::internal::CaptureStdout();
    LOG_INFO_MSG(kExpectedMessage);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find(kExpectedMessage), std::string::npos);
    EXPECT_NE(output.find(expectedLevel), std::string::npos);
}

TEST(TestLoggerMessage, LogWarningMessage) {
    const std::string expectedLevel = "WARNING";

    testing::internal::CaptureStdout();
    LOG_WARNING_MSG(kExpectedMessage);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find(kExpectedMessage), std::string::npos);
    EXPECT_NE(output.find(expectedLevel), std::string::npos);
}

TEST(TestLoggerMessage, LogErrorMessage) {
    const std::string expectedLevel = "ERROR";

    testing::internal::CaptureStderr();
    LOG_ERROR_MSG(kExpectedMessage);
    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_NE(output.find(kExpectedMessage), std::string::npos);
    EXPECT_NE(output.find(expectedLevel), std::string::npos);
}

TEST(TestLoggerMessage, LogFatalMessage) {
    const std::string expectedLevel = "FATAL";

    testing::internal::CaptureStderr();
    LOG_FATAL_MSG(kExpectedMessage);
    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_NE(output.find(kExpectedMessage), std::string::npos);
    EXPECT_NE(output.find(expectedLevel), std::string::npos);
}
