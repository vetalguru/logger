// Copyright (c) 2025 Vitalii Shkibtan. All rights reserved.

#ifndef INCLUDE_LOGGER_HPP_
#define INCLUDE_LOGGER_HPP_

// Threading support is enabled by default.
// Define LOGGER_NO_THREAD_SUPPORT before including this file to disable
// mutex usage.
#ifndef LOGGER_NO_THREAD_SUPPORT
#define LOGGER_USE_MUTEX
#endif

#include <chrono>   // NOLINT(build/c++11)
#include <iostream>
#include <fstream>
#include <functional>
#include <memory>
#ifdef LOGGER_USE_MUTEX
#include <mutex>    // NOLINT(build/c++11)
#endif
#include <string>
#include <sstream>
#include <iomanip>


class Logger{
 public:
    enum class LogLevel { TRACE, DEBUG, INFO, WARNING, ERROR, FATAL };

    using LogHandler = std::function<void(const std::string&)>;

    struct Target {
        LogLevel level;
        LogHandler handler;
    };

    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    bool setLogFile(const std::string& aFileName, LogLevel aLevel = LogLevel::TRACE) {
#ifdef LOGGER_USE_MUTEX
        std::lock_guard<std::mutex> lock(m_mutex);
#endif
        auto file = std::make_shared<std::ofstream>(aFileName, std::ios::app);
        if (!file->is_open()) {
            return false;
        }

        addHandler([file](const std::string& aMessage) {
            (*file) << aMessage << std::endl;
            file->flush();
        }, aLevel);

        return true;
    }

    void addHandler(const LogHandler& aHandler, LogLevel aLevel) {
#ifdef LOGGER_USE_MUTEX
        std::lock_guard<std::mutex> lock(m_mutex);
#endif
        m_targets.push_back({aLevel, aHandler});
    }

    void log(LogLevel aLevel, const std::string& aMessage) {
#ifdef LOGGER_USE_MUTEX
        std::lock_guard<std::mutex> lock(m_mutex);
#endif
        if (!shouldLog(aLevel)) {
            return;
        }

        std::string formatted = formatMessage(aLevel, aMessage);

        for (const auto& target : m_targets) {
            if (aLevel >= target.level) {
                target.handler(formatted);
            }
        }
    }

    class LogStream {
     public:
        explicit LogStream(LogLevel aLevel) : m_level(aLevel) {}
        ~LogStream() { Logger::getInstance().log(m_level, m_buffer.str()); }

        template<typename T>
        LogStream& operator<<(const T& aValue) {
            m_buffer << aValue;
            return *this;
        }

     private:
        LogLevel m_level;
        std::ostringstream m_buffer;
    };

    static void trace_msg(const std::string& msg) { getInstance().log(LogLevel::TRACE, msg); }
    static void debug_msg(const std::string& msg) { getInstance().log(LogLevel::DEBUG, msg); }
    static void info_msg(const std::string& msg) { getInstance().log(LogLevel::INFO, msg); }
    static void warning_msg(const std::string& msg) { getInstance().log(LogLevel::WARNING, msg); }
    static void error_msg(const std::string& msg) { getInstance().log(LogLevel::ERROR, msg); }
    static void fatal_msg(const std::string& msg) { getInstance().log(LogLevel::FATAL, msg); }

    static LogStream trace()   { return LogStream(LogLevel::TRACE); }
    static LogStream debug()   { return LogStream(LogLevel::DEBUG); }
    static LogStream info()    { return LogStream(LogLevel::INFO); }
    static LogStream warning() { return LogStream(LogLevel::WARNING); }
    static LogStream error()   { return LogStream(LogLevel::ERROR); }
    static LogStream fatal()   { return LogStream(LogLevel::FATAL); }

 private:
    Logger() {
        // Default console output
        // for messages
        addHandler([](const std::string& aMessage) {
            std::cout << aMessage << std::endl;
        }, LogLevel::INFO);

        // for errors
        addHandler([](const std::string& aMessage) {
            std::cerr << aMessage << std::endl;
        }, LogLevel::ERROR);
    }

    ~Logger() = default;

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    bool shouldLog(LogLevel aLevel) {
        for (const auto & target : m_targets) {
            if (aLevel >= target.level) {
                return false;
            }
        }
        return true;
    }

    std::string logLevelToString(LogLevel aLevel) {
        switch (aLevel) {
            case LogLevel::TRACE: return "TRACE";
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR: return "ERROR";
            case LogLevel::FATAL: return "FATAL";
            default: return "UNKNOWN";
        }
    }

    std::string getCurrentTime() {
        using namespace std::chrono;
        auto now = system_clock::now();
        auto time = system_clock::to_time_t(now);
        auto usec = duration_cast<microseconds>(
            now.time_since_epoch()) % 1'000'000;

        std::tm localTime;
        localtime_r(&time, &localTime);

        std::ostringstream oss;
        oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S")
            << "." << std::setfill('0') << std::setw(6) << usec.count();
        return oss.str();
    }

    std::string formatMessage(LogLevel aLevel,
        const std::string& aMessage) {
        std::ostringstream output;
        output << "[" << getCurrentTime() << "] ["
            << logLevelToString(aLevel) << "]\t" << aMessage;
        return output.str();
    }

 private:
#ifdef LOGGER_USE_MUTEX
    std::mutex m_mutex;
#endif
    std::vector<Target> m_targets;
};

#define LOG_ENABLE_FILE(aFile)  Logger::getInstance().setLogFile(aFile)
#define LOG_DISABLE_FILE()      Logger::getInstance().addHandler([](const std::string&) {}, Logger::LogLevel::FATAL)

#define LOG_TRACE_MSG(aMessage)     Logger::trace_msg(aMessage)
#define LOG_DEBUG_MSG(aMessage)     Logger::debug_msg(aMessage)
#define LOG_INFO_MSG(aMessage)      Logger::info_msg(aMessage)
#define LOG_WARNING_MSG(aMessage)   Logger::warning_msg(aMessage)
#define LOG_ERROR_MSG(aMessage)     Logger::error_msg(aMessage)
#define LOG_FATAL_MSG(aMessage)     Logger::fatal_msg(aMessage)

#define LOG_TRACE       Logger::trace()
#define LOG_DEBUG       Logger::debug()
#define LOG_INFO        Logger::info()
#define LOG_WARNING     Logger::warning()
#define LOG_ERROR       Logger::error()
#define LOG_FATAL       Logger::fatal()

#endif  // INCLUDE_LOGGER_HPP_
