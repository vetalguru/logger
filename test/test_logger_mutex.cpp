// Copyright (c) 2025 Vitalii Shkibtan. All rights reserved.

#include <gtest/gtest.h>

#ifdef LOGGER_USE_MUTEX
#include <mutex>  // NOLINT(build/c++11)
#endif

#include "include/logger.hpp"

TEST(LoggerMutex, MutexDefined) {
#ifdef LOGGER_USE_MUTEX
    // Check that std::mutex is defined
    std::mutex test_mutex;
    EXPECT_TRUE(true);  // If we got here, the test passed
#else
    GTEST_SKIP() << "LOGGER_USE_MUTEX is not defined, skipping test.";
#endif
}
