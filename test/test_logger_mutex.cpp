// Copyright (c) 2025 Vitalii Shkibtan. All rights reserved.

#include <gtest/gtest.h>

#ifdef LOGGER_USE_MUTEX
#include <mutex>  // NOLINT(build/c++11)
#endif

#include "include/logger.hpp"


TEST(LoggerMutex, MutexDefined) {
#ifdef LOGGER_USE_MUTEX
    std::mutex test_mutex;
    EXPECT_TRUE(true);
#else
    EXPECT_TRUE(false) << "LOGGER_USE_MUTEX is not defined.";
#endif
}
