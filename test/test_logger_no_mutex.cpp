// Copyright (c) 2025 Vitalii Shkibtan. All rights reserved.

#include <gtest/gtest.h>

#define LOGGER_NO_THREAD_SUPPORT
#include "include/logger.hpp"

#ifdef LOGGER_USE_MUTEX
#include <mutex>  // NOLINT(build/c++11)
#endif


TEST(LoggerMutex, MutexNotDefined) {
#ifdef LOGGER_USE_MUTEX
    std::mutex test_mutex;
    EXPECT_TRUE(false);
#else
    EXPECT_TRUE(true) << "LOGGER_USE_MUTEX is not defined.";
#endif
}
